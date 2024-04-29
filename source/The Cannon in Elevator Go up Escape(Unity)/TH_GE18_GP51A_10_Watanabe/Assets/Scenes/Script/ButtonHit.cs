using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ButtonHit : MonoBehaviour
{
    private new GameObject light;

    public Material lightMaterial;           // 割り当てるマテリアル.
    public Material noLightMaterial;

    // Start is called before the first frame update
    void Start()
    {
        light = transform.Find("Light").gameObject;
    }

    // Update is called once per frame
    void Update()
    {

    }

    public void ButtonLite()
    {
        light.GetComponent<Renderer>().material = lightMaterial;
    }

    public void ButtonNoLite()
    {
        light.GetComponent<Renderer>().material = noLightMaterial;
    }
}
