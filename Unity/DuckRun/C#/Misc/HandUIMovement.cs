using UnityEngine;

public class HandUIMovement : MonoBehaviour
{
    public float MoveSpeed = 5f;

    public float DownLimit = -200f;
    public float UpLimit = 200f;

    private Vector2 OriginalPosition;
    private RectTransform RectTransform;

    public bool MovingDown = false;
    public bool MovingUp = false;

    void Start()
    {
        RectTransform = GetComponent<RectTransform>();

        OriginalPosition = RectTransform.anchoredPosition;
    }

    void Update()
    {
        if (MovingDown)
        {
            MoveDown();
        }

        if (MovingUp)
        {
            MoveUp();
        }
    }

    void MoveDown()
    {
        if (RectTransform.anchoredPosition.y <= DownLimit)
        {
            RectTransform.anchoredPosition = OriginalPosition;
        }
        else
        {
            RectTransform.anchoredPosition += Vector2.down * MoveSpeed * Time.deltaTime;
        }
    }

    void MoveUp()
    {
        if (RectTransform.anchoredPosition.y >= UpLimit)
        {
            RectTransform.anchoredPosition = OriginalPosition;
        }
        else
        {
            RectTransform.anchoredPosition += Vector2.up * MoveSpeed * Time.deltaTime;
        }
    }
}
