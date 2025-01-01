using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FixCracklyAndroidAudio : MonoBehaviour
{
    public AudioSource bgmsource;

    void Awake()
    {
        AudioConfiguration config = AudioSettings.GetConfiguration();
        config.dspBufferSize = 500;
        AudioSettings.Reset(config);

        if (!bgmsource.isPlaying)
        {
            bgmsource.Play();
        }
    }

    // Start is called before the first frame update
    void Start()
    {


    }

    // Update is called once per frame
    void Update()
    {

    }
}
