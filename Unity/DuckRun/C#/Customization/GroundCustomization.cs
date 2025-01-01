using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GroundCustomization : MonoBehaviour
{
    [Header("Ground/Ceiling")]
    public GameObject Ceiling;
    public GameObject Floor;

    [Header("Savefile")]
    public SaveFile saveFile;

    [Header("Vaporwave Background")]
    public Color[] CeilingGround;

    [Header("Mountain Background")]
    public Color[] CeilingGround2;

    [Header("Clouds Background")]
    public Color[] CeilingGround3;

    [Header("Forest Background")]
    public Color[] CeilingGround4;
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
            Ceiling.GetComponent<SpriteRenderer>().color = CeilingGround[0];
            Floor.GetComponent<SpriteRenderer>().color = CeilingGround[0];
        }

        if (saveFile.SelectedBackgroundItem.ItemName == "Mountains")
        {
            Ceiling.GetComponent<SpriteRenderer>().color = CeilingGround2[0];
            Floor.GetComponent<SpriteRenderer>().color = CeilingGround2[0];
        }

        if (saveFile.SelectedBackgroundItem.ItemName == "Clouds")
        {
            Ceiling.GetComponent<SpriteRenderer>().color = CeilingGround3[0];
            Floor.GetComponent<SpriteRenderer>().color = CeilingGround3[0];
        }

        if (saveFile.SelectedBackgroundItem.ItemName == "Forest")
        {
            Ceiling.GetComponent<SpriteRenderer>().color = CeilingGround4[0];
            Floor.GetComponent<SpriteRenderer>().color = CeilingGround4[0];
        }
    }
}
