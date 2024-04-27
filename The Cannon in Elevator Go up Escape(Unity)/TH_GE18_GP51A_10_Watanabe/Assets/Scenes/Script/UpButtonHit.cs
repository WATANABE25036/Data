using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using static UnityEngine.UI.CanvasScaler;

public class UpButtonHit : MonoBehaviour
{
    private new GameObject light;
    AudioSource audioSource;
    float pitchUp = 0;
    bool downTrigger;

    public float flashInterval;
    public float flashCnt;
    public Material lightMaterial;           // 割り当てるマテリアル
    public Material noLightMaterial;           // 割り当てるマテリアル
    public static bool upHit;
    public static bool trigger;
    public AudioClip switchOn;

    // Start is called before the first frame update
    void Start()
    {
        light = transform.Find("Light").gameObject;
        audioSource = GetComponent<AudioSource>();
        trigger = false;
    }

    // Update is called once per frame
    void Update()
    {
        upHit = false;
        //downTrigger = DownButtonHit.trigger;
    }

    void OnCollisionEnter(Collision col)
    {
        if(!trigger)
        {
            StartCoroutine("Coroutine");
        }
    }

    private IEnumerator Coroutine()
    {
        trigger = true;

        audioSource.pitch = 1.0f;
        audioSource.PlayOneShot(switchOn);
        light.GetComponent<Renderer>().material = lightMaterial;
        yield return new WaitForSeconds(flashInterval);

        for (int i = 0; i < flashCnt; i++)
        {
            light.GetComponent<Renderer>().material = noLightMaterial;
            yield return new WaitForSeconds(flashInterval);

            pitchUp += 0.1f;
            audioSource.pitch = 1.0f + pitchUp;
            audioSource.PlayOneShot(switchOn);
            light.GetComponent<Renderer>().material = lightMaterial;
            yield return new WaitForSeconds(flashInterval);
        }

        upHit = true;
    }
}