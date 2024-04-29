using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LightControl : MonoBehaviour
{
    GameObject lightRight, lightLeft, lightCenter;
    public AudioSource audioSourceL;
    public AudioSource audioSourceR;
    public AudioSource audioSourceC;

    public static LightControl instance;
    public AudioClip lightOn;

    public void Awake()
    {
        if (instance == null)
        {
            instance = this;
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        lightRight = GameObject.Find("LightRight");
        lightLeft = GameObject.Find("LightLeft");
        lightCenter = GameObject.Find("LightCenter");
    }

    // Update is called once per frame
    void Update()
    {

    }

    public void lightRightFun(bool lightRightCon)
    {
        audioSourceC.pitch = 1.0f + Random.Range(-0.2f, 0.2f);
        audioSourceC.PlayOneShot(lightOn);

        lightRight.SetActive(lightRightCon);
    }

    public void lightLeftFun(bool lightLeftCon)
    {
        audioSourceC.pitch = 1.0f + Random.Range(-0.2f, 0.2f);
        audioSourceC.PlayOneShot(lightOn);

        lightLeft.SetActive(lightLeftCon);
    }

    public void lightCenterFun(bool lightCenterCon)
    {
        audioSourceC.pitch = 1.0f + Random.Range(-0.2f, 0.2f);
        audioSourceC.PlayOneShot(lightOn);

        lightCenter.SetActive(lightCenterCon);
    }

    public void lightRightSilentFun(bool lightRightCon)
    {
        lightRight.SetActive(lightRightCon);
    }

    public void lightLeftSilentFun(bool lightLeftCon)
    {
        lightLeft.SetActive(lightLeftCon);
    }

    public void lightCenterSilentFun(bool lightCenterCon)
    {
        lightCenter.SetActive(lightCenterCon);
    }
}
