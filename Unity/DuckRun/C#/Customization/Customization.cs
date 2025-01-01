using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Customization : MonoBehaviour
{
    [Header("Unlockable Items")]
    public BackgroundImages[] BackgroundImagesItemsList;
    public PlayerImages[] PlayerImagesItemsList;
    public BirdImages[] BirdImagesItemsList;
    public CatImages[] CatImagesItemsList;

    public Dictionary<string, BackgroundImages> BackgroundImagesItemsDictionary = new Dictionary<string, BackgroundImages>();
    public Dictionary<string, PlayerImages> PlayerImagesItemsDictionary = new Dictionary<string, PlayerImages>();
    public Dictionary<string, BirdImages> BirdImagesItemsDictionary = new Dictionary<string, BirdImages>();
    public Dictionary<string, CatImages> CatImagesItemsDictionary = new Dictionary<string, CatImages>();

    [Serializable]
    public struct BackgroundImages
    {
        public string ItemName;
        public Sprite[] sprite;
        public int Cost;
    }

    [Serializable]
    public struct PlayerImages
    {
        public string ItemName;
        public RuntimeAnimatorController anim;
        public int Cost;
    }

    [Serializable]
    public struct BirdImages
    {
        public string ItemName;
        public RuntimeAnimatorController anim;
        public int Cost;
    }

    [Serializable]
    public struct CatImages
    {
        public string ItemName;
        public RuntimeAnimatorController anim;
        public int Cost;
    }

    public void Start()
    {
        foreach (var item in BackgroundImagesItemsList)
        {
            BackgroundImagesItemsDictionary.Add(item.ItemName, item);
        }

        foreach (var item in PlayerImagesItemsList)
        {
            PlayerImagesItemsDictionary.Add(item.ItemName, item);
        }

        foreach (var item in BirdImagesItemsList)
        {
            BirdImagesItemsDictionary.Add(item.ItemName, item);
        }

        foreach (var item in CatImagesItemsList)
        {
            CatImagesItemsDictionary.Add(item.ItemName, item);
        }
    }

    public Dictionary<string, object> FindItem(string ItemName)
    {
        var result = new Dictionary<string, object>();

        if (BackgroundImagesItemsDictionary.TryGetValue(ItemName, out var backgroundItem))
        {
            result["Background"] = backgroundItem;
            return result;
        }

        else if (PlayerImagesItemsDictionary.TryGetValue(ItemName, out var playerItem))
        {
            result["Player"] = playerItem;
            return result;
        }

        else if (BirdImagesItemsDictionary.TryGetValue(ItemName, out var birdItem))
        {
            result["Bird"] = birdItem;
            return result;
        }

        else if (CatImagesItemsDictionary.TryGetValue(ItemName, out var catItem))
        {
            result["Cat"] = catItem;
            return result;
        }

        else if (result.Count == 0)
        {
            Debug.LogError("Item + " + ItemName + " not found in any dictionary");
        }

        return result;
    }

    public RuntimeAnimatorController GetBirdAnim(string ItemName)
    {
        if (BirdImagesItemsDictionary.TryGetValue(ItemName, out BirdImages var))
        {
            return var.anim;
        }
        else
        {
            Debug.Log("COULD NOT FIND RUNTIMEANIMCONTROLLER GETBIRDANIM");
            return null;
        }
    }

    public RuntimeAnimatorController GetCatAnim(string ItemName)
    {
        if (CatImagesItemsDictionary.TryGetValue(ItemName, out CatImages var))
        {
            return var.anim;
        }
        else
        {
            Debug.Log("COULD NOT FIND RUNTIMEANIMCONTROLLER GetCatAnim");
            return null;
        }
    }

    public Sprite[] GetBackgroundSprites(string ItemName)
    {
        if (BackgroundImagesItemsDictionary.TryGetValue(ItemName, out BackgroundImages var))
        {
            return var.sprite;
        }
        else
        {
            Debug.Log("COULD NOT FIND Sprite[] GetBackgroundSprites");
            return null;
        }
    }

    public RuntimeAnimatorController GetPlayerAnim(string ItemName)
    {
        if (PlayerImagesItemsDictionary.TryGetValue(ItemName, out PlayerImages var))
        {
            return var.anim;
        }
        else
        {
            Debug.Log("COULD NOT FIND RUNTIMEANIMCONTROLLER GetPlayerAnim");
            return null;
        }
    }
}
