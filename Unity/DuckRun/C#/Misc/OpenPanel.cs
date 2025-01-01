using System.Collections;
using UnityEngine;

public class OpenPanel : MonoBehaviour
{
    public GameObject[] PanelToOpen;
    public GameObject[] ThingsToHide;

    [Header("Credits Button Specific")]
    public bool MoveCamCreditsButton;
    public float Speed;

    private bool StallUpdate = true;
    private bool MoveCamCreditsButtonRight = false;
    private bool MoveCamCreditsButtonLeft = false;

    [Header("Credits Button Specific")]
    public AudioManager audioManager;

    public void OnClickShowEnter()
    {
        audioManager.audioSource.PlayOneShot(audioManager.ButtonClick);
        StartCoroutine(OnClickShow());
    }

    public void OnClickHideEnter()
    {
        audioManager.audioSource.PlayOneShot(audioManager.ButtonClick);
        StartCoroutine(OnClickHide());
    }

    public void Update()
    {
        if (StallUpdate == true)
        {
            return;
        }
        else
        {
            if (MoveCamCreditsButtonRight)
            {
                GameObject g = GameObject.FindGameObjectWithTag("MainCamera");
                g.transform.position = Vector3.MoveTowards(g.transform.position, new Vector3(6, 0, -10), Speed * Time.deltaTime);
            }

            if (MoveCamCreditsButtonLeft)
            {
                GameObject g = GameObject.FindGameObjectWithTag("MainCamera");
                g.transform.position = Vector3.MoveTowards(g.transform.position, new Vector3(0, 0, -10), Speed * Time.deltaTime);
            }
        }
    }
    // Start is called before the first frame update
    private IEnumerator OnClickShow()
    {
        foreach (GameObject g in ThingsToHide)
        {
            g.SetActive(false);
        }

        if (MoveCamCreditsButton)
        {
            MoveCamCreditsButtonRight = true;
            StallUpdate = false;
            yield return new WaitForSeconds(0.05f);
            MoveCamCreditsButtonRight = false;
            StallUpdate = true;
        }

        foreach (GameObject g in PanelToOpen)
        {
            g.SetActive(true);
        }
        yield return null;
    }

    private IEnumerator OnClickHide()
    {
        foreach (GameObject g in PanelToOpen)
        {
            g.SetActive(false);
        }

        if (MoveCamCreditsButton)
        {
            MoveCamCreditsButtonLeft = true;
            StallUpdate = false;
            yield return new WaitForSeconds(0.05f);
            MoveCamCreditsButtonLeft = false;
            StallUpdate = true;
        }

        foreach (GameObject g in ThingsToHide)
        {
            g.SetActive(true);
        }

        yield return null;
    }
}
