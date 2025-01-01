using System.Collections;
using UnityEngine;

public class ParallaxBackground : MonoBehaviour
{
    public float ScrollSpeed;
    public float ParallaxEffectMultiplier;
    public Transform NextBackground;

    private float TextureWidth;
    private Camera MainCamera;
    private float CameraWidth;

    public Rules rules;

    void Start()
    {
        SpriteRenderer SpriteRenderer = GetComponent<SpriteRenderer>();
        TextureWidth = SpriteRenderer.bounds.size.x;

        MainCamera = Camera.main;
        CameraWidth = MainCamera.orthographicSize * 2 * MainCamera.aspect;
        StartCoroutine(Initialize());
    }

    IEnumerator Initialize()
    {
        yield return new WaitForSeconds(1.1f);

        SpriteRenderer SpriteRenderer = GetComponent<SpriteRenderer>();
        TextureWidth = SpriteRenderer.bounds.size.x;

        CameraWidth = MainCamera.orthographicSize * 2 * MainCamera.aspect;
    }

    void Update()
    {
        if (rules.Movement && TextureWidth > 0)
        {
            float displacement = Time.deltaTime * ScrollSpeed * ParallaxEffectMultiplier;
            transform.Translate(Vector3.left * displacement);

            if (IsOutOfView())
            {
                AlignToNextBackground();
            }
        }
    }

    bool IsOutOfView()
    {
        float BackgroundRightEdge = transform.position.x + TextureWidth / 2;

        float CameraLeftEdge = MainCamera.transform.position.x - CameraWidth / 2;

        if (BackgroundRightEdge < CameraLeftEdge)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void AlignToNextBackground()
    {
        if (NextBackground != null)
        {
            float NextBackgroundRightEdge = NextBackground.position.x + NextBackground.GetComponent<SpriteRenderer>().bounds.size.x / 2;

            float NewPositionX = NextBackgroundRightEdge + (TextureWidth / 2) - 0.1f;

            transform.position = new Vector3(NewPositionX, transform.position.y, transform.position.z);
        }
    }

}
