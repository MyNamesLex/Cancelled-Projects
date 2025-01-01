using System;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEngine.SceneManagement;
using TMPro;
using System.Collections;

public class SaveFile : MonoBehaviour
{
    [Header("High Score")]
    public int HighScore;

    [Header("Currency")]
    public int InGameCurrency;

    [Header("States")]
    public bool Loaded = false;

    [Header("Unlocked Background Items")]
    public UnlockedBackgroundItem[] UnlockedBackgroundList;
    public Dictionary<string, UnlockedBackgroundItem> UnlockedBackgroundDictionary = new Dictionary<string, UnlockedBackgroundItem>();

    [Header("Unlocked Player Items")]
    public UnlockedPlayerItem[] UnlockedPlayerList;
    public Dictionary<string, UnlockedPlayerItem> UnlockedPlayerDictionary = new Dictionary<string, UnlockedPlayerItem>();

    [Header("Unlocked Bird Items")]
    public UnlockedBirdItem[] UnlockedBirdList;
    public Dictionary<string, UnlockedBirdItem> UnlockedBirdDictionary = new Dictionary<string, UnlockedBirdItem>();

    [Header("Unlocked Cat Items")]
    public UnlockedCatItem[] UnlockedCatList;
    public Dictionary<string, UnlockedCatItem> UnlockedCatDictionary = new Dictionary<string, UnlockedCatItem>();

    [Header("Selected Items (Store Item Names)")]
    public UnlockedBackgroundItem SelectedBackgroundItem;
    public UnlockedPlayerItem SelectedPlayerItem;
    public UnlockedBirdItem SelectedBirdItem;
    public UnlockedCatItem SelectedCatItem;

    [Header("Customization")]
    public Customization customization;

    [Header("SampleScene Selectable Skins")]
    public GameObject[] Background;
    public GameObject Player;
    public Animator PlayerAnim;
    public GameObject[] Cat;
    public GameObject[] Bird;

    private string saveFilePath;
    private RuntimeAnimatorController catanim;
    private RuntimeAnimatorController birdanim;

    [Serializable]
    public struct UnlockedBackgroundItem
    {
        public string ItemName;

        public UnlockedBackgroundItem(string itemName)
        {
            ItemName = itemName;
        }

        public Dictionary<string, object> ToDictionary()
        {
            return new Dictionary<string, object>
        {
            { "ItemName", ItemName },
        };
        }
    }

    [Serializable]
    public struct UnlockedPlayerItem
    {
        public string ItemName;

        public UnlockedPlayerItem(string itemName)
        {
            ItemName = itemName;
        }

        public Dictionary<string, object> ToDictionary()
        {
            return new Dictionary<string, object>
        {
            { "ItemName", ItemName },
        };
        }
    }

    [Serializable]
    public struct UnlockedBirdItem
    {
        public string ItemName;

        public UnlockedBirdItem(string itemName)
        {
            ItemName = itemName;
        }

        public Dictionary<string, object> ToDictionary()
        {
            return new Dictionary<string, object>
        {
            { "ItemName", ItemName },
        };
        }
    }

    [Serializable]
    public struct UnlockedCatItem
    {
        public string ItemName;

        public UnlockedCatItem(string itemName)
        {
            ItemName = itemName;
        }

        public Dictionary<string, object> ToDictionary()
        {
            return new Dictionary<string, object>
        {
            { "ItemName", ItemName },
        };
        }
    }

    private void Awake()
    {
        saveFilePath = Path.Combine(Application.persistentDataPath, "savefile.json");
    }

    private void Start()
    {
        LoadData();
        PopulateDictionaries();

        customization = GameObject.FindGameObjectWithTag("Customization").GetComponent<Customization>();

        if (SceneManager.GetActiveScene().name == "SampleScene")
        {
            StartCoroutine(ApplySelectedSkins());
        }
    }

    IEnumerator ApplySelectedSkins()
    {
        yield return new WaitForSeconds(0.1f);

        Sprite[] bgsprites = customization.GetBackgroundSprites(SelectedBackgroundItem.ItemName);

        Vector3 DefaultSize = Vector3.zero;
        if (Background.Length > 0 && Background[0] != null)
        {
            SpriteRenderer spriteRenderer = Background[0].GetComponent<SpriteRenderer>();
            if (spriteRenderer != null)
            {
                DefaultSize = spriteRenderer.bounds.size;
            }
        }

        Vector3 DefaultScale = new Vector3(3.1f, 3.1f, 1);

        for (int i = 0; i < Background.Length; i++)
        {
            SpriteRenderer BackgroundSpriteRenderer = null;
            if (Background[i] != null)
            {
                BackgroundSpriteRenderer = Background[i].GetComponent<SpriteRenderer>();
            }

            if (BackgroundSpriteRenderer == null || i >= bgsprites.Length)
            {
                Debug.Log("Invalid sprite or missing SpriteRenderer at index " + i.ToString());
                continue;
            }

            if (bgsprites[i] != null)
            {
                BackgroundSpriteRenderer.sprite = bgsprites[i];
                Vector3 currentSize = BackgroundSpriteRenderer.bounds.size;

                if (currentSize != Vector3.zero)
                {
                    Vector3 scaleAdjustment = new Vector3(
                        (DefaultSize.x / currentSize.x) * DefaultScale.x,
                        (DefaultSize.y / currentSize.y) * DefaultScale.y,
                        DefaultScale.z
                    );
                    Background[i].transform.localScale = scaleAdjustment;
                }
            }
        }

        if (Player != null)
        {
            Animator playerAnimator = Player.GetComponent<Animator>();
            if (playerAnimator != null)
            {
                playerAnimator.runtimeAnimatorController = customization.GetPlayerAnim(SelectedPlayerItem.ItemName);
            }
        }
    }


    public void Update()
    {
        if (SceneManager.GetActiveScene().name == "SampleScene")
        {
            if (catanim == null)
            {
                catanim = customization.GetCatAnim(SelectedCatItem.ItemName);
            }

            if (birdanim == null)
            {
                birdanim = customization.GetBirdAnim(SelectedBirdItem.ItemName);
            }

            GameObject[] cats = GameObject.FindGameObjectsWithTag("Cat");
            GameObject[] birds = GameObject.FindGameObjectsWithTag("Bird");

            foreach (GameObject cat in cats)
            {
                Animator CatAnimator = cat.GetComponent<Animator>();
                if (CatAnimator != null && catanim != null && CatAnimator.runtimeAnimatorController != null)
                {
                    CatAnimator.runtimeAnimatorController = catanim;
                }
            }

            // Apply selected Bird animations
            foreach (GameObject bird in birds)
            {
                Animator BirdAnimator = bird.GetComponent<Animator>();
                if (BirdAnimator != null && birdanim != null && BirdAnimator.runtimeAnimatorController != null)
                {
                    BirdAnimator.runtimeAnimatorController = birdanim;
                }
            }
        }
    }

    void PopulateDictionaries()
    {
        UnlockedBackgroundDictionary.Clear();
        foreach (var item in UnlockedBackgroundList)
        {
            UnlockedBackgroundDictionary[item.ItemName] = item;
        }

        UnlockedPlayerDictionary.Clear();
        foreach (var item in UnlockedPlayerList)
        {
            UnlockedPlayerDictionary[item.ItemName] = item;
        }

        UnlockedBirdDictionary.Clear();
        foreach (var item in UnlockedBirdList)
        {
            UnlockedBirdDictionary[item.ItemName] = item;
        }

        UnlockedCatDictionary.Clear();
        foreach (var item in UnlockedCatList)
        {
            UnlockedCatDictionary[item.ItemName] = item;
        }
    }

    public Dictionary<string, object> FindItem(string itemName)
    {
        Dictionary<string, object> result = new Dictionary<string, object>();

        if (UnlockedBackgroundDictionary.ContainsKey(itemName))
        {
            result = UnlockedBackgroundDictionary[itemName].ToDictionary();
        }

        else if (UnlockedPlayerDictionary.ContainsKey(itemName))
        {
            result = UnlockedPlayerDictionary[itemName].ToDictionary();
        }

        else if (UnlockedBirdDictionary.ContainsKey(itemName))
        {
            result = UnlockedBirdDictionary[itemName].ToDictionary();
        }

        else if (UnlockedCatDictionary.ContainsKey(itemName))
        {
            result = UnlockedCatDictionary[itemName].ToDictionary();
        }
        else
        {
            Debug.LogError("Item " + itemName.ToString() + " not found in any dictionary");
        }

        return result;
    }


    public void SaveData()
    {
        SaveDataFormat data = new SaveDataFormat
        {
            HighScore = HighScore,
            InGameCurrency = InGameCurrency,
            UnlockedBackgroundItemNames = UnlockedBackgroundList,
            UnlockedPlayerItemNames = UnlockedPlayerList,
            UnlockedBirdItemNames = UnlockedBirdList,
            UnlockedCatItemNames = UnlockedCatList,
            SelectedBackgroundItemName = SelectedBackgroundItem,
            SelectedPlayerItemName = SelectedPlayerItem,
            SelectedBirdItemName = SelectedBirdItem,
            SelectedCatItemName = SelectedCatItem,
        };

        string json = JsonUtility.ToJson(data);
        File.WriteAllText(saveFilePath, json);
        Debug.Log("Data saved to " + saveFilePath);
    }

    public void LoadData()
    {
        if (File.Exists(saveFilePath))
        {
            string json = File.ReadAllText(saveFilePath);
            SaveDataFormat data = JsonUtility.FromJson<SaveDataFormat>(json);

            HighScore = data.HighScore;
            InGameCurrency = data.InGameCurrency;

            SelectedBackgroundItem = data.SelectedBackgroundItemName;
            SelectedPlayerItem = data.SelectedPlayerItemName;
            SelectedBirdItem = data.SelectedBirdItemName;
            SelectedCatItem = data.SelectedCatItemName;
            UnlockedCatList = data.UnlockedCatItemNames;
            UnlockedPlayerList = data.UnlockedPlayerItemNames;
            UnlockedBirdList = data.UnlockedBirdItemNames;
            UnlockedBackgroundList = data.UnlockedBackgroundItemNames;

            Debug.Log("Data loaded from " + saveFilePath);
            PopulateDictionaries();

            Loaded = true;

            if (SceneManager.GetActiveScene().name == "SampleScene")
            {
                TextMeshProUGUI HSText = GameObject.FindGameObjectWithTag("HSText").GetComponent<TextMeshProUGUI>();
                HSText.text = "High Score: " + HighScore;
            }
        }
        else
        {
            Debug.Log("No save file found at " + saveFilePath);
        }
    }

    [Serializable]
    public class SaveDataFormat
    {
        public int HighScore;
        public int InGameCurrency;
        public UnlockedBackgroundItem[] UnlockedBackgroundItemNames;
        public UnlockedPlayerItem[] UnlockedPlayerItemNames;
        public UnlockedBirdItem[] UnlockedBirdItemNames;
        public UnlockedCatItem[] UnlockedCatItemNames;
        public UnlockedBackgroundItem SelectedBackgroundItemName;
        public UnlockedPlayerItem SelectedPlayerItemName;
        public UnlockedBirdItem SelectedBirdItemName;
        public UnlockedCatItem SelectedCatItemName;
    }
    public string ReturnInGameCurrency()
    {
        return InGameCurrency.ToString();
    }
}
