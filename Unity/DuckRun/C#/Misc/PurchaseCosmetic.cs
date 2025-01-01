using System.Collections;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class PurchaseCosmetic : MonoBehaviour
{
    public AudioManager AudioManager;
    public SaveFile saveFile;
    public Customization customization;
    public ScrollItemNameDisplay scrollItemNameDisplay;
    public TextMeshProUGUI ButtonText;
    public string ItemName;
    public int Cost;

    public TextMeshProUGUI NotEnoughMoneyText;

    public InGameCurrencyText igct;

    public bool BoughtItem = false;

    [SerializeField]
    public object cosmetic;
    public void Awake()
    {
        BoughtItem = false;
    }

    IEnumerator NotEnoughTextTimer()
    {
        NotEnoughMoneyText.text = "Not Enough Coins";
        yield return new WaitForSeconds(3);
        NotEnoughMoneyText.text = "";
        yield return null;
    }

    public void OnClick()
    {
        if (BoughtItem == false)
        {
            AudioManager.audioSource.PlayOneShot(AudioManager.ButtonClick);

            if (cosmetic is Customization.BirdImages birdItem)
            {
                saveFile.UnlockedBirdDictionary[birdItem.ItemName] = new SaveFile.UnlockedBirdItem(birdItem.ItemName);

                int NewSize = saveFile.UnlockedBirdList.Length + 1;
                SaveFile.UnlockedBirdItem[] NewArray = new SaveFile.UnlockedBirdItem[NewSize];

                for (int i = 0; i < saveFile.UnlockedBirdList.Length; i++)
                {
                    NewArray[i] = saveFile.UnlockedBirdList[i];
                }

                NewArray[NewSize - 1] = new SaveFile.UnlockedBirdItem(birdItem.ItemName);

                saveFile.UnlockedBirdList = NewArray;

                saveFile.SelectedBirdItem = new SaveFile.UnlockedBirdItem(birdItem.ItemName);

                BoughtItem = true;
            }

            else if (cosmetic is Customization.BackgroundImages backgroundItem)
            {
                saveFile.UnlockedBackgroundDictionary[backgroundItem.ItemName] = new SaveFile.UnlockedBackgroundItem(backgroundItem.ItemName);

                int NewSize = saveFile.UnlockedBackgroundList.Length + 1;
                SaveFile.UnlockedBackgroundItem[] NewArray = new SaveFile.UnlockedBackgroundItem[NewSize];
                for (int i = 0; i < saveFile.UnlockedBackgroundList.Length; i++)
                {
                    NewArray[i] = saveFile.UnlockedBackgroundList[i];
                }
                NewArray[NewSize - 1] = new SaveFile.UnlockedBackgroundItem(backgroundItem.ItemName);

                saveFile.UnlockedBackgroundList = NewArray;

                for (int i = 0; i < backgroundItem.sprite.Length; i++)
                {
                    saveFile.SelectedBackgroundItem.ItemName = backgroundItem.ItemName;
                }
                BoughtItem = true;
            }

            else if (cosmetic is Customization.CatImages catItem)
            {
                saveFile.UnlockedCatDictionary[catItem.ItemName] = new SaveFile.UnlockedCatItem(catItem.ItemName);

                int NewSize = saveFile.UnlockedCatList.Length + 1;
                SaveFile.UnlockedCatItem[] NewArray = new SaveFile.UnlockedCatItem[NewSize];
                for (int i = 0; i < saveFile.UnlockedCatList.Length; i++)
                {
                    NewArray[i] = saveFile.UnlockedCatList[i];
                }
                NewArray[NewSize - 1] = new SaveFile.UnlockedCatItem(catItem.ItemName);

                saveFile.UnlockedCatList = NewArray;

                saveFile.SelectedCatItem = new SaveFile.UnlockedCatItem(catItem.ItemName);
                BoughtItem = true;
            }

            else if (cosmetic is Customization.PlayerImages playerItem)
            {
                saveFile.UnlockedPlayerDictionary[playerItem.ItemName] = new SaveFile.UnlockedPlayerItem(playerItem.ItemName);

                int NewSize = saveFile.UnlockedPlayerList.Length + 1;
                SaveFile.UnlockedPlayerItem[] NewArray = new SaveFile.UnlockedPlayerItem[NewSize];
                for (int i = 0; i < saveFile.UnlockedPlayerList.Length; i++)
                {
                    NewArray[i] = saveFile.UnlockedPlayerList[i];
                }
                NewArray[NewSize - 1] = new SaveFile.UnlockedPlayerItem(playerItem.ItemName);

                saveFile.UnlockedPlayerList = NewArray;

                saveFile.SelectedPlayerItem = new SaveFile.UnlockedPlayerItem(playerItem.ItemName);
                BoughtItem = true;
            }

            igct.InGameCurrencyTMP.text = "Coins: " + saveFile.ReturnInGameCurrency();

            saveFile.SaveData();

            StartCoroutine(disable());
        }
    }

    void OnDisable()
    {
        BoughtItem = false;
    }

    IEnumerator disable()
    {
        yield return new WaitForSeconds(0.5f);
        gameObject.SetActive(false);
    }

}
