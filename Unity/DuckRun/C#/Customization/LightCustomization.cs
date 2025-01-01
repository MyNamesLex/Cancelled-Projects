using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LightCustomization : MonoBehaviour
{
    [Header("Savefile")]
    public SaveFile saveFile;

    [Header("Vaporwave Background")]
    public GameObject[] Lights;

    [Header("Mountain Background")]
    public GameObject[] Lights2;

    [Header("Clouds Background")]
    public GameObject[] Lights3;

    [Header("Forest Background")]
    public GameObject[] Lights4;
    // Start is called before the first frame update
    void Start()
    {
        StartCoroutine(WaitForSettings());
    }

    IEnumerator WaitForSettings()
    {
        yield return new WaitForSeconds(0.5f);
        if (saveFile.SelectedBackgroundItem.ItemName == "Vaporwave")
        {
            foreach (GameObject g in Lights)
            {
                g.SetActive(true);
            }
        }

        if (saveFile.SelectedBackgroundItem.ItemName == "Clouds")
        {
            foreach (GameObject g in Lights3)
            {
                g.SetActive(true);
            }
        }

        if (saveFile.SelectedBackgroundItem.ItemName == "Mountains")
        {
            foreach (GameObject g in Lights2)
            {
                g.SetActive(true);
            }
        }

        if (saveFile.SelectedBackgroundItem.ItemName == "Forest")
        {
            foreach (GameObject g in Lights4)
            {
                g.SetActive(true);
            }
        }
    }

    // Update is called once per frame
    void Update()
    {

    }
}
