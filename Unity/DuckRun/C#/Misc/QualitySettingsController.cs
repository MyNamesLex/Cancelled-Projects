using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class QualitySettingsController : MonoBehaviour
{
    public TMP_Dropdown qualitydropdown;
    void Start()
    {

        if (qualitydropdown != null)
        {
            qualitydropdown.value = QualitySettings.GetQualityLevel();
            qualitydropdown.onValueChanged.AddListener(ChangeQualityLevel);
        }
    }

    public void ChangeQualityLevel(int qualityIndex)
    {
        QualitySettings.SetQualityLevel(qualityIndex, true);
    }

    public void IncreaseQuality()
    {
        int CurrentLevel = QualitySettings.GetQualityLevel();
        if (CurrentLevel < QualitySettings.names.Length - 1)
        {
            QualitySettings.SetQualityLevel(CurrentLevel + 1, true);
        }
    }

    public void DecreaseQuality()
    {
        int CurrentLevel = QualitySettings.GetQualityLevel();
        if (CurrentLevel > 0)
        {
            QualitySettings.SetQualityLevel(CurrentLevel - 1, true);
        }
    }
}
