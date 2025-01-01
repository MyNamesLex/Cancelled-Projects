using System;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEngine.SceneManagement;
using TMPro;
using System.Collections;


public class ScaleSpriteToCollider : MonoBehaviour
{
    public Vector3 DefaultSpriteScale = new Vector3(0.5f, 0.5f, 0.5f);

    void Start()
    {
        StartCoroutine(Wait());
    }

    IEnumerator Wait()
    {
        yield return new WaitForSeconds(1);
        SpriteRenderer SpriteRenderer = GetComponent<SpriteRenderer>();

        if (SpriteRenderer.sprite.name.Contains("floter"))
        {
            AdjustSpriteScale();
        }
        yield return null;
    }

    void AdjustSpriteScale()
    {
        SpriteRenderer SpriteRenderer = GetComponent<SpriteRenderer>();
        BoxCollider2D BoxCollider = GetComponent<BoxCollider2D>();

        if (SpriteRenderer != null && BoxCollider != null)
        {
            float SpriteWidth = SpriteRenderer.bounds.size.x;
            float SpriteHeight = SpriteRenderer.bounds.size.y;
            float BoxWidth = BoxCollider.size.x;
            float BoxHeight = BoxCollider.size.y;

            float scaleFactor = Mathf.Max(BoxWidth / SpriteWidth, BoxHeight / SpriteHeight) * DefaultSpriteScale.x;

            transform.localScale = new Vector3(scaleFactor, scaleFactor, DefaultSpriteScale.z);

            BoxCollider.size = new Vector2(.12f, .12f);
        }
    }
}

