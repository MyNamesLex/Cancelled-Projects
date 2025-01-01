using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestObject : MonoBehaviour
{
    public GameObject end;
    public float speed;
    public Rules rules;
    public Animator anim;
    public Environment e;

    public EdgeCollider2D ec2;
    // Start is called before the first frame update
    void Start()
    {
        Rigidbody2D rb = GetComponent<Rigidbody2D>();
        if (name.Contains("Bird"))
        {
            rb.isKinematic = true;
        }

        GameObject rulesg = GameObject.FindGameObjectWithTag("Rules");
        rules = rulesg.GetComponent<Rules>();

        GameObject g = GameObject.FindGameObjectWithTag("Environment");
        e = g.GetComponent<Environment>();

        if (transform.position.y > 0)
        {
            rb.gravityScale = -1;
            end = GameObject.FindGameObjectWithTag("EndTop");
        }
        else
        {
            end = GameObject.FindGameObjectWithTag("End");
        }

        if (name.Contains("Bird"))
        {
            end = GameObject.FindGameObjectWithTag("EndMid");
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (rules.Movement)
        {
            transform.position = Vector3.MoveTowards(transform.position, end.transform.position, speed * Time.deltaTime);
            if (name.Contains("Bird") == false)
            {
                anim.SetBool("Run", true);
            }
        }
        else
        {
            if (name.Contains("Bird") == false)
            {
                anim.SetBool("Run", false);
            }
        }
    }
}
