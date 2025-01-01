using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PauseAndResumeButton : MonoBehaviour
{
    [Header("PausePlay Sprites")]
    public Sprite PauseSprite;
    public Sprite PlaySprite;

    [Header("GameObjects")]
    public GameObject OnScreenPauseButton;
    public GameObject PausePanel;

    [Header("Values")]
    public Rules rules;

    public bool IsPaused;

    public void OnClick()
    {
        IsPaused = !IsPaused;

        rules.Movement = !IsPaused;

        PausePanel.SetActive(IsPaused);

        if (IsPaused)
        {
            OnScreenPauseButton.GetComponent<Image>().sprite = PlaySprite;
        }
        else
        {
            OnScreenPauseButton.GetComponent<Image>().sprite = PauseSprite;
        }
    }
}
