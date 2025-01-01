using System.Collections;
using Unity.Mathematics;
using UnityEngine;
using TMPro;
using UnityEngine.Rendering.Universal;
using UnityEngine.EventSystems;
using System.Collections.Generic;

public class PlayerMovement : MonoBehaviour
{
    [Header("Movement")]
    public Rigidbody2D rb;
    public float speed;
    public float JumpHeight;
    public float FallMultiplier;
    public float LowJumpMultiplier;

    public BoxCollider2D bc2dTrigger;
    public BoxCollider2D bc2dNoneTrigger;

    [Header("Ground")]
    public float RayLength;
    public LayerMask GroundMask;
    public bool OnGround = false;

    [Header("Camera")]
    public CameraController cam;

    [Header("Visuals")]
    public ParticleSystem SwapVFX;
    public GameObject HowToPlayUI;
    public GameObject PauseButton;

    [Header("Rules")]
    public Rules rules;
    public SaveFile saveFile;
    public Points p;
    public Animator anim;

    [Header("Dead Stats")]
    public GameObject DeadPanel;
    public LayerMask enemylayermask;
    public bool point = true;
    private GameObject LastDeathObject = null;
    public TextMeshProUGUI PointsText;

    [Header("AudioManager")]
    public AudioManager am;

    [Header("Debug")]
    public bool Debugging;
    public TextMeshProUGUI FPSText;
    public TextMeshProUGUI QualityText;
    private string[] QualityLevels;
    private string CurrentQuality;
    private Vector2 StartTouchPosition;
    private float SwipeThreshold = 50f;
    private float DeltaTime;
    public TextMeshProUGUI SpawnTrackerText;
    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
        enemylayermask = ~enemylayermask;
        StartCoroutine(AdjustHitbox());
    }
    IEnumerator AdjustHitbox()
    {
        yield return new WaitForSeconds(1);
        if (GetComponent<Animator>().runtimeAnimatorController.name == "Player2Anim")
        {
            bc2dTrigger.offset = new Vector2(0.000828742981f, 7.74860382e-07f);
            bc2dTrigger.size = new Vector2(0.239476681f, 0.283311248f);
            bc2dNoneTrigger.offset = new Vector2(0.000828742981f, 7.74860382e-07f);
            bc2dNoneTrigger.size = new Vector2(0.239476681f, 0.283311248f);
        }

        yield return null;
    }

    // Update is called once per frame
    void Update()
    {
        if (Debugging)
        {
            DebugFunc();
        }

        if (rules.Movement == true)
        {
            anim.SetBool("Walking", true);
            anim.SetBool("Idle", false);

            // input
            if (Input.touchCount > 0)
            {
                Touch touch = Input.GetTouch(0);

                if (EventSystem.current.IsPointerOverGameObject(touch.fingerId) == false)
                {
                    if (touch.phase == TouchPhase.Began && PauseButton.GetComponent<PauseAndResumeButton>().IsPaused == false)
                    {
                        StartTouchPosition = touch.position;

                        if (OnGround && PauseButton.GetComponent<PauseAndResumeButton>().IsPaused == false)
                        {
                            Jump();
                        }
                    }

                    // Detect movement and check for a swipe
                    if (touch.phase == TouchPhase.Moved)
                    {
                        Vector2 SwipeDirection = touch.position - StartTouchPosition;

                        if (Mathf.Abs(SwipeDirection.y) > SwipeThreshold)
                        {
                            // Swipe up: Reverse gravity
                            if (SwipeDirection.y > 0 && rb.gravityScale == 1 && OnGround)
                            {
                                rb.gravityScale = -1;
                                StartCoroutine(Snap());
                                StartTouchPosition = touch.position;
                            }
                            // Swipe down: Restore gravity
                            else if (SwipeDirection.y < 0 && rb.gravityScale == -1 && OnGround)
                            {
                                rb.gravityScale = 1;
                                StartCoroutine(Snap());
                                StartTouchPosition = touch.position;
                            }
                        }
                    }
                }
            }
            if (Input.GetKeyDown(KeyCode.Space) && OnGround)
            {
                Jump();
            }

            // grav flip

            if (Input.GetKeyDown(KeyCode.G) && rb.gravityScale == 1 && OnGround)
            {
                rb.gravityScale = -1;
                StartCoroutine(Snap());
            }

            else if (Input.GetKeyDown(KeyCode.G) && rb.gravityScale == -1 && OnGround)
            {
                rb.gravityScale = 1;
                StartCoroutine(Snap());
            }

            // Jump Modifiers

            if (rb.gravityScale == 1) // Normal Gravity
            {
                if (rb.velocity.y < 0) // Falling down
                {
                    rb.velocity += Vector2.up * Physics2D.gravity.y * (FallMultiplier - 1) * Time.deltaTime;
                }
                else if (rb.velocity.y > 0) // Short jump: key released
                {
                    rb.velocity += Vector2.up * Physics2D.gravity.y * (LowJumpMultiplier - 1) * Time.deltaTime;
                }
            }

            else if (rb.gravityScale == -1) // Inverted Gravity
            {
                if (rb.velocity.y > 0) // Falling up (since gravity is flipped)
                {
                    rb.velocity += Vector2.down * Physics2D.gravity.y * (FallMultiplier - 1) * Time.deltaTime;
                }
                else if (rb.velocity.y < 0) // Short jump when gravity is flipped
                {
                    rb.velocity += Vector2.down * Physics2D.gravity.y * (LowJumpMultiplier - 1) * Time.deltaTime;
                }
            }

            // ground detect

            if (rb.gravityScale == 1)
            {
                RaycastHit2D ray = Physics2D.Raycast(transform.position, Vector2.down, RayLength, GroundMask);
                if (ray.collider != null)
                {
                    OnGround = true;
                }
                else
                {
                    OnGround = false;
                }
            }
            else if (rb.gravityScale == -1)
            {
                RaycastHit2D ray = Physics2D.Raycast(transform.position, Vector2.up, RayLength, GroundMask);
                if (ray.collider != null)
                {
                    OnGround = true;
                }
                else
                {
                    OnGround = false;
                }
            }

            // point detect

            if (rb.gravityScale == 1)
            {
                // Raycast downwards
                RaycastHit2D ray = Physics2D.Raycast(transform.position, Vector2.down, 30, enemylayermask);

                if (ray.collider != null && ray.collider.gameObject.tag == "Cat")
                {
                    // Only award a point if this is a new Death object
                    if (!point && ray.collider.gameObject != LastDeathObject)
                    {
                        p.Point++;
                        point = true;
                        LastDeathObject = ray.collider.gameObject;
                        am.audioSource.PlayOneShot(am.JumpedOverCatSFX);
                        Debug.Log("Point awarded :D");
                    }
                }
                else if (ray.collider == null || ray.collider.gameObject.tag != "Cat")
                {
                    point = false;
                }
            }
            else if (rb.gravityScale == -1)
            {
                RaycastHit2D ray = Physics2D.Raycast(transform.position, Vector2.up, 30, enemylayermask);

                if (ray.collider != null && ray.collider.gameObject.tag == "Cat")
                {
                    if (!point && ray.collider.gameObject != LastDeathObject)
                    {
                        p.Point++;
                        point = true;
                        LastDeathObject = ray.collider.gameObject;
                        am.audioSource.PlayOneShot(am.JumpedOverCatSFX);
                        Debug.Log("Point awarded!");
                    }
                }
                else if (ray.collider == null || ray.collider.gameObject.tag != "Cat")
                {
                    point = false;
                }
            }
        }
        else
        {
            GameObject g = GameObject.FindGameObjectWithTag("HSText");

            if (g != null)
            {
                TextMeshProUGUI HSText = GameObject.FindGameObjectWithTag("HSText").GetComponent<TextMeshProUGUI>();
                HSText.text = "High Score: " + saveFile.HighScore;
            }

            anim.SetBool("Idle", true);
            anim.SetBool("Walking", false);
            if (Input.touchCount > 0 && anim.GetBool("Dead") == false && PauseButton.GetComponent<PauseAndResumeButton>().IsPaused == false || Input.anyKeyDown && anim.GetBool("Dead") == false && PauseButton.GetComponent<PauseAndResumeButton>().IsPaused == false)
            {
                am.audioSource.PlayOneShot(am.ButtonClick);
                PauseButton.SetActive(true);
                HowToPlayUI.SetActive(false);
                rules.Movement = true;
            }
        }

        if (PauseButton.GetComponent<PauseAndResumeButton>().IsPaused == true)
        {
            anim.SetBool("Idle", true);
            anim.SetBool("Walking", false);
            anim.SetBool("Jumping", false);
        }

        if (rb.gravityScale == -1)
        {
            GetComponent<ShadowCaster2D>().castsShadows = false;
        }
        else
        {
            GetComponent<ShadowCaster2D>().castsShadows = true;
        }
    }

    // jump/grav switch

    IEnumerator Snap()
    {
        ParticleSystem SwapVFXIns = Instantiate(SwapVFX, new Vector3(transform.position.x, transform.position.y, 10), quaternion.identity);
        SpriteRenderer SpriteRenderer = GetComponent<SpriteRenderer>();

        var shape = SwapVFXIns.shape;

        if (rb.gravityScale == -1)
        {
            am.audioSource.PlayOneShot(am.GravityFlipDownToUp);
            SpriteRenderer.flipY = true;
            shape.rotation = new Vector3(0, 0, 0);
            SwapVFXIns.Play();
            rb.gravityScale = -10;
            yield return new WaitForSeconds(0.5f);
            rb.gravityScale = -1;
            yield return new WaitForSeconds(0.5f);
            SwapVFXIns.Stop();
            yield return null;
        }

        if (rb.gravityScale == 1)
        {
            am.audioSource.PlayOneShot(am.GravityFlipUpToDown);
            shape.rotation = new Vector3(180, 0, 0);
            SpriteRenderer.flipY = false;
            SwapVFXIns.Play();
            rb.gravityScale = 10;
            yield return new WaitForSeconds(0.5f);
            rb.gravityScale = 1;
            yield return new WaitForSeconds(0.5f);
            SwapVFXIns.Stop();
            yield return null;
        }
    }

    public void Jump()
    {
        if (PauseButton.GetComponent<PauseAndResumeButton>().IsPaused == false)
        {
            am.audioSource.PlayOneShot(am.JumpSFX);
            StartCoroutine(JumpAnim());

            rb.velocity = new Vector2(rb.velocity.x, 0);
            float jumpVelocity = Mathf.Sqrt(2 * Mathf.Abs(Physics2D.gravity.y) * JumpHeight);

            if (rb.gravityScale == 1)
            {
                rb.velocity = new Vector2(rb.velocity.x, jumpVelocity);
            }
            else
            {
                rb.velocity = new Vector2(rb.velocity.x, -jumpVelocity);
            }
        }
    }

    // collision

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Cat" || collision.gameObject.tag == "Bird")
        {
            Debug.Log("Dead Hit " + collision.gameObject.name);
            rb.velocity = new Vector2(0, 0);
            rules.Movement = false;

            PauseButton.SetActive(false);
            PauseButton.GetComponent<PauseAndResumeButton>().PausePanel.SetActive(false);

            GameObject[] deathlist = GameObject.FindGameObjectsWithTag("Cat");
            foreach (GameObject g in deathlist)
            {
                g.GetComponent<Rigidbody2D>().bodyType = RigidbodyType2D.Static;
            }

            GameObject[] deathlist2 = GameObject.FindGameObjectsWithTag("Bird");
            foreach (GameObject g in deathlist2)
            {
                g.GetComponent<Rigidbody2D>().bodyType = RigidbodyType2D.Static;
            }

            StartCoroutine(DeadAnim());
        }

        if (collision.gameObject.tag == "Ground" && rules.Movement == false && HowToPlayUI.activeInHierarchy == false)
        {
            am.audioSource.PlayOneShot(am.DeadSFX);
        }
    }

    // Animation

    public IEnumerator JumpAnim()
    {
        anim.SetBool("Jumping", true);
        yield return new WaitForSeconds(1);
        anim.SetBool("Jumping", false);
        yield return null;
    }
    public IEnumerator DeadAnim()
    {
        anim.SetBool("Dead", true);
        yield return new WaitForSeconds(2);
        DeadPanelFunc();
    }

    // Pause/Win

    public void DeadPanelFunc()
    {
        DeadPanel.SetActive(true);

        TextMeshProUGUI HSText = GameObject.FindGameObjectWithTag("HSText").GetComponent<TextMeshProUGUI>();
        HSText.text = "High Score: " + saveFile.HighScore;
        //medals

        if (p.Point < 10)
        {

        }

        if (p.Point > 10)
        {
            p.MedalImage.sprite = p.BronzeMedal;
        }

        if (p.Point > 20)
        {
            p.MedalImage.sprite = p.SilverMedal;
        }

        if (p.Point > 30)
        {
            p.MedalImage.sprite = p.GoldMedal;
        }

        if (p.Point > saveFile.HighScore)
        {
            saveFile.HighScore = p.Point;
            saveFile.InGameCurrency += 25;
        }

        saveFile.SaveData();

        PointsText.text = p.Point.ToString();
    }

    // Debug

    public void DebugFunc()
    {
        FPSTextFunc();
        QualityTextFunc();
        SpawnTracker();
    }

    public void FPSTextFunc()
    {
        DeltaTime += (Time.unscaledDeltaTime - DeltaTime) * 0.1f;
        float fps = 1.0f / DeltaTime;
        FPSText.text = Mathf.Ceil(fps).ToString() + " FPS";
    }

    public void QualityTextFunc()
    {
        QualityLevels = QualitySettings.names;

        CurrentQuality = QualityLevels[QualitySettings.GetQualityLevel()];

        QualityText.text = CurrentQuality;
    }

    public void SpawnTracker()
    {
        int Bird = 0;
        int Cat = 0;
        GameObject[] glist = GameObject.FindGameObjectsWithTag("Cat");
        foreach (GameObject g in glist)
        {
            if (g.name.Contains("Cat"))
            {
                Cat++;
            }
        }

        GameObject[] glist2 = GameObject.FindGameObjectsWithTag("Bird");
        foreach (GameObject g in glist2)
        {
            if (g.name.Contains("Bird"))
            {
                Bird++;
            }
        }

        SpawnTrackerText.text = "Bird: " + Bird + "| Cat: " + Cat;
    }
}
