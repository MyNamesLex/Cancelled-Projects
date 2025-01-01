using UnityEngine;
using TMPro;

public class LetterBounce : MonoBehaviour
{
    public TMP_Text tmp;
    public float BounceVel = 2;
    public float BounceSpeed = 1f;

    private TMP_TextInfo TextInfo;
    private Vector3[][] OriginalVertices;

    private void Start()
    {
        tmp.ForceMeshUpdate();
        TextInfo = tmp.textInfo;

        OriginalVertices = new Vector3[TextInfo.meshInfo.Length][];
        for (int i = 0; i < OriginalVertices.Length; i++)
        {
            OriginalVertices[i] = TextInfo.meshInfo[i].vertices.Clone() as Vector3[];
        }
    }

    private void Update()
    {
        AnimateLetters();
    }

    void AnimateLetters()
    {
        tmp.ForceMeshUpdate();
        TextInfo = tmp.textInfo;

        for (int i = 0; i < TextInfo.characterCount; i++)
        {
            if (!TextInfo.characterInfo[i].isVisible)
                continue;

            int MaterialIndex = TextInfo.characterInfo[i].materialReferenceIndex;

            int VertexIndex = TextInfo.characterInfo[i].vertexIndex;

            Vector3[] vertices = TextInfo.meshInfo[MaterialIndex].vertices;

            float bounce = Mathf.Sin(Time.time * BounceSpeed + i * 0.1f) * BounceVel;

            vertices[VertexIndex + 0].y = OriginalVertices[MaterialIndex][VertexIndex + 0].y + bounce;
            vertices[VertexIndex + 1].y = OriginalVertices[MaterialIndex][VertexIndex + 1].y + bounce;
            vertices[VertexIndex + 2].y = OriginalVertices[MaterialIndex][VertexIndex + 2].y + bounce;
            vertices[VertexIndex + 3].y = OriginalVertices[MaterialIndex][VertexIndex + 3].y + bounce;
        }

        for (int i = 0; i < TextInfo.meshInfo.Length; i++)
        {
            TextInfo.meshInfo[i].mesh.vertices = TextInfo.meshInfo[i].vertices;
            tmp.UpdateGeometry(TextInfo.meshInfo[i].mesh, i);
        }
    }
}
