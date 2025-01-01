using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Audio;

public class AudioControlSliders : MonoBehaviour
{
    public AudioMixer AudioMixer;
    public string Parameter;

    public void SliderValueChange(float val)
    {
        AudioMixer.SetFloat(Parameter, val);
    }
}
