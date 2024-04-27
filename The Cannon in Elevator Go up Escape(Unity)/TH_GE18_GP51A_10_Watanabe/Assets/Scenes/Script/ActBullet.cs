using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ActBullet : MonoBehaviour
{
    AudioSource audioSource;
    float startTime; //発射時刻

    public AudioClip bounceSound;

    void Start()
    {
        DontDestroyOnLoad(this);

        startTime = Time.time; //発射された時刻を覚えておく
        audioSource = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        if (startTime + 100.0f < Time.time) //発射から...秒経ったら
        {
            Destroy(this.gameObject); //自身を削除
        }
    }

    //何かにぶつかったら
    void OnCollisionEnter(Collision col)
    {
        //何かにぶつかったときの音
        audioSource.pitch = 0.5f + Random.Range(-0.3f, 0.3f);//ピッチをランダムに再生
        audioSource.PlayOneShot(bounceSound);
    }
}
