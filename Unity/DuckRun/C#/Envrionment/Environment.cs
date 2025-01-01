using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class Environment : MonoBehaviour
{
    public PlayerMovement player;
    public Rules rules;

    [Header("Locations")]
    public GameObject Spawn;
    public GameObject End;

    [Header("Objects")]
    public List<GameObject> Objs;

    [Header("Times")]
    public List<int> RNGTimeToSpawn;


    // Start is called before the first frame update
    void Start()
    {
        if (rules.Movement)
        {
            StartCoroutine(Timer());
        }
        else
        {
            StartCoroutine(Loop());
        }
    }

    public IEnumerator Loop()
    {
        if (rules.Movement == false)
        {
            yield return new WaitForSeconds(0.5f);
            StartCoroutine(Loop());
            yield return null;
        }
        else
        {
            Start();
        }
    }

    // Update is called once per frame
    void Update()
    {

    }

    IEnumerator Timer()
    {
        System.Random r = new System.Random();
        int rng = r.Next(RNGTimeToSpawn[0], RNGTimeToSpawn[1]);
        yield return new WaitForSeconds(rng);
        SpawnObj();
        StartCoroutine(Timer());
    }

    public void SpawnObj()
    {
        if (rules.Movement == true)
        {
            if (Spawn.name.Contains("Top"))
            {
                System.Random r = new System.Random();
                int rng = r.Next(0, Objs.Count);
                GameObject g = Instantiate(Objs[rng], Spawn.transform.position, Quaternion.identity);
                g.transform.rotation = new Quaternion(180, 0, 0, 0);
            }
            else
            {
                System.Random r = new System.Random();
                int rng = r.Next(0, Objs.Count);
                GameObject g = Instantiate(Objs[rng], Spawn.transform.position, Quaternion.identity);
            }
        }
    }
}
