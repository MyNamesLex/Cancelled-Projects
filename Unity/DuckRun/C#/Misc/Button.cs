using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Button : MonoBehaviour
{
    public AudioManager AudioManager;
    public string OpenLevelString;
    public bool Quitting;

    public void OnClick()
    {
        AudioManager.audioSource.PlayOneShot(AudioManager.ButtonClick);
        if (Quitting)
        {
#if UNITY_EDITOR
            UnityEditor.EditorApplication.isPlaying = false;
#else
            Application.Quit();
#endif
        }
        else
        {
            StartCoroutine(OnClickCoroutine());
        }
    }

    IEnumerator OnClickCoroutine()
    {
        yield return new WaitForSeconds(0.5f);
        SceneManager.LoadScene(OpenLevelString);
    }
}
