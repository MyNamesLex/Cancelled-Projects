using UnityEngine;
using UnityEngine.UI;
using System.Collections.Generic;
using TMPro;
using System.Collections;
using Unity.VisualScripting;

public class ScrollItemNameDisplay : MonoBehaviour
{
    public ScrollRect ScrollRect;
    public TextMeshProUGUI ItemNameText;
    public RectTransform content;
    public List<GameObject> items;

    private SaveFile saveFile;
    public Customization customization;
    public PurchaseCosmetic PurchaseCosmetic;
    private GameObject LastCenteredItem;

    private void Start()
    {
        var obj = GameObject.FindGameObjectWithTag("SaveFile");
        if (obj != null)
        {
            saveFile = obj.GetComponent<SaveFile>();
        }

        if (PurchaseCosmetic != null)
        {
            PurchaseCosmetic.gameObject.SetActive(false);
        }
    }

    private void Update()
    {
        GameObject CenteredItem = GetCenteredItem();

        if (CenteredItem != null && CenteredItem != LastCenteredItem)
        {
            ItemNameText.text = CenteredItem.name;
            Debug.Log("Centered Item: " + CenteredItem.name);
            LastCenteredItem = CenteredItem;

            if (saveFile != null)
            {
                GetSelectedItem();
            }
        }
    }

    public void GetSelectedItem()
    {
        Dictionary<string, object> SelectedItem = null;
        // Check if saveFile is not null before calling FindItem
        if (saveFile != null)
        {
            SelectedItem = saveFile.FindItem(ItemNameText.text);
        }

        if (SelectedItem == null || SelectedItem.Count == 0)
        {
            Dictionary<string, object> SelectedItemInCustomization = null;

            // Check if customization is not null before calling FindItem
            if (customization != null)
            {
                SelectedItemInCustomization = customization.FindItem(ItemNameText.text);
            }

            if (SelectedItemInCustomization != null && SelectedItemInCustomization.Count > 0)
            {
                DisplayPurchaseOption(SelectedItemInCustomization);
            }
            else
            {
                if (PurchaseCosmetic != null)
                {
                    PurchaseCosmetic.gameObject.SetActive(false);
                }
            }
        }
        else
        {
            if (PurchaseCosmetic != null)
            {
                PurchaseCosmetic.gameObject.SetActive(false);
            }
            StartCoroutine(AssignSelectedItem(SelectedItem, saveFile));
        }
    }


    private void DisplayPurchaseOption(Dictionary<string, object> SelectedItemInCustomization)
    {
        if (SelectedItemInCustomization.TryGetValue("Background", out var BackgroundObj) &&
            BackgroundObj is Customization.BackgroundImages BackgroundItem)
        {
            ActivatePurchaseUI(BackgroundObj);
        }
        else if (SelectedItemInCustomization.TryGetValue("Player", out var PlayerObj) &&
                 PlayerObj is Customization.PlayerImages PlayerItem)
        {
            ActivatePurchaseUI(PlayerObj);
        }
        else if (SelectedItemInCustomization.TryGetValue("Bird", out var BirdObj) &&
                 BirdObj is Customization.BirdImages BirdItem)
        {
            ActivatePurchaseUI(BirdObj);
        }
        else if (SelectedItemInCustomization.TryGetValue("Cat", out var CatObj) &&
                 CatObj is Customization.CatImages CatItem)
        {
            ActivatePurchaseUI(CatObj);
        }
    }

    private void ActivatePurchaseUI(object cosmetic)
    {
        if (PurchaseCosmetic != null)
        {
            if (cosmetic is Customization.BackgroundImages BGItem && BGItem.Cost > 0)
            {
                PurchaseCosmetic.Cost = BGItem.Cost;
            }
            if (cosmetic is Customization.PlayerImages PItem && PItem.Cost > 0)
            {
                PurchaseCosmetic.Cost = PItem.Cost;
            }
            if (cosmetic is Customization.CatImages CItem && CItem.Cost > 0)
            {
                PurchaseCosmetic.Cost = CItem.Cost;
            }
            if (cosmetic is Customization.BirdImages BItem && BItem.Cost > 0)
            {
                PurchaseCosmetic.Cost = BItem.Cost;
            }

            PurchaseCosmetic.gameObject.SetActive(true);
            PurchaseCosmetic.ItemName = ItemNameText.text;
            PurchaseCosmetic.ButtonText.text = "Purchase: \n" + PurchaseCosmetic.ItemName + " Cost: " + PurchaseCosmetic.Cost;
            PurchaseCosmetic.cosmetic = cosmetic;
        }
    }

    IEnumerator AssignSelectedItem(Dictionary<string, object> SelectedItem, SaveFile saveFile)
    {
        if (SelectedItem == null)
        {
            Debug.LogError("SelectedItem is null");
            yield break;
        }

        if (SelectedItem.TryGetValue("ItemName", out var ItemName))
        {
            string ItemNameAsString = ItemName.ToString();
            if (string.IsNullOrEmpty(ItemNameAsString))
            {
                Debug.LogError("ItemName is null");
                yield break;
            }

            if (saveFile.UnlockedBackgroundDictionary.TryGetValue(ItemNameAsString, out var BackgroundItem))
            {
                saveFile.SelectedBackgroundItem = (SaveFile.UnlockedBackgroundItem)BackgroundItem;
            }
            else if (saveFile.UnlockedPlayerDictionary.TryGetValue(ItemNameAsString, out var PlayerItem))
            {
                saveFile.SelectedPlayerItem = (SaveFile.UnlockedPlayerItem)PlayerItem;
            }
            else if (saveFile.UnlockedBirdDictionary.TryGetValue(ItemNameAsString, out var BirdItem))
            {
                saveFile.SelectedBirdItem = (SaveFile.UnlockedBirdItem)BirdItem;
            }
            else if (saveFile.UnlockedCatDictionary.TryGetValue(ItemNameAsString, out var CatItem))
            {
                saveFile.SelectedCatItem = (SaveFile.UnlockedCatItem)CatItem;
            }
        }

        saveFile.SaveData();

        yield return null;
    }



    private GameObject GetCenteredItem()
    {
        Vector3 ViewportCenterWorldPos = ScrollRect.viewport.position;
        GameObject ClosestItem = null;
        float ClosestDistance = float.MaxValue;

        foreach (GameObject item in items)
        {
            RectTransform ItemRectTransform = item.GetComponent<RectTransform>();
            float distance = Vector3.Distance(ViewportCenterWorldPos, ItemRectTransform.position);

            if (distance < ClosestDistance)
            {
                ClosestDistance = distance;
                ClosestItem = item;
            }
        }
        return ClosestItem;
    }
}
