using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraShake : MonoBehaviour
{
    bool oldShake = false;
    Vector3 cameraPos;

    public static bool shake = false;

    public float magnitude = 0.03f;

    // Start is called before the first frame update
    void Start()
    {
        cameraPos = new Vector3(transform.localPosition.x, transform.localPosition.y, transform.localPosition.z);
    }

    // Update is called once per frame
    void Update()
    {
        if(shake == true)
        {
            var x = cameraPos.x + Random.Range(-0.1f, 0.1f) * magnitude;
            var y = cameraPos.y + Random.Range(-0.1f, 0.1f) * magnitude;

            transform.localPosition = new Vector3(x, y, cameraPos.z);
        }
        else//シェイク終了
        {
            transform.localPosition = cameraPos;
        }
    }
}
