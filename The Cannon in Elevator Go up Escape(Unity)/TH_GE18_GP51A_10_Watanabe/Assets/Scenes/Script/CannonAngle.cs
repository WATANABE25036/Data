using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CannonAngle : MonoBehaviour
{
    GameObject muzzle;
    public AudioSource audioSourceHorizon;
    public AudioSource audioSourceVertical;
    public AudioClip horizonSound;
    public AudioClip verticalSound;

    void Start()
    {
        DontDestroyOnLoad(this);
        muzzle = transform.Find("Muzzle").gameObject;//子オブジェクトを指定
    }

    void Update()
    {
        float inputX = Input.GetAxisRaw("Horizontal");
        float inputY = Input.GetAxisRaw("Vertical");

        var oldRotX = this.transform.rotation;

        //回転させるQuaternionを作成
        Quaternion rotationX = Quaternion.AngleAxis(inputX, Vector3.up);
        //現在の自身の回転の情報を取得する
        Quaternion quaternionX = this.transform.rotation;
        //合成して、自身に設定
        this.transform.rotation = quaternionX * rotationX;

        if (oldRotX != this.transform.rotation && !audioSourceHorizon.isPlaying)//再生が終わってから再生する
        {
            audioSourceHorizon.pitch = 1.0f + Random.Range(-0.3f, 0.3f);//ピッチをランダムに再生
            audioSourceHorizon.PlayOneShot(horizonSound);
        }

        if (oldRotX == this.transform.rotation) audioSourceHorizon.Stop();

        var oldRotY = muzzle.transform.rotation;

        //回転させるQuaternionを作成
        Quaternion rotationY = Quaternion.AngleAxis(inputY, Vector3.left);
        //現在の自身の回転の情報を取得する
        Quaternion quaternionY = muzzle.transform.rotation;
        //合成して、自身に設定
        muzzle.transform.rotation = quaternionY * rotationY;

        if (oldRotY != muzzle.transform.rotation && !audioSourceVertical.isPlaying)//再生が終わってから再生する
        {
            audioSourceVertical.pitch = 1.0f + Random.Range(-0.3f, 0.3f);//ピッチをランダムに再生
            audioSourceVertical.PlayOneShot(verticalSound);
        }

        if(oldRotY == muzzle.transform.rotation) audioSourceVertical.Stop();

        if (Input.GetKeyDown(KeyCode.R))
        {
            audioSourceHorizon.PlayOneShot(horizonSound);
            audioSourceVertical.PlayOneShot(verticalSound);
            transform.rotation = Quaternion.Euler(0, 180, 0);
            muzzle.transform.rotation = Quaternion.Euler(0, 180, 0);
        }
    }
}
