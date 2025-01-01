using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class InGameCurrencyText : MonoBehaviour
{
    public TextMeshProUGUI InGameCurrencyTMP;
    public SaveFile sf;
    // Start is called before the first frame update
    void Start()
    {
        StartCoroutine(WaitForLoad());
    }

    public IEnumerator WaitForLoad()
    {
        if (sf.Loaded == false)
        {
            yield return new WaitForSeconds(0.1f);
            StartCoroutine(WaitForLoad());
            InGameCurrencyTMP.text = "Coins: 0";
            StopCoroutine(WaitForLoad());
        }
        else
        {
            InGameCurrencyTMP.text = "Coins: " + sf.ReturnInGameCurrency();
            yield return null;
        }
    }

    // Update is called once per frame
    void Update()
    {

    }
}
