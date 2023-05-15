using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InverseKinematic : MonoBehaviour
{
    public Transform target;

    public Transform root;
    public Transform[] chains;
    public float[] chainsLength;

    public bool invert;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        CalcIK(target.position); 
    }

    void CalcIK(Vector3 _point) {

        Vector3 _dir = _point - chains[0].position;

        Vector3 offset = _dir.sqrMagnitude > 0.01f? Vector3.Cross(_dir, Vector3.up).normalized: Vector3.right;
        Vector3 point = _point + (offset * 2.4f);
        
        Vector3 dir = point - chains[0].position;
        float distance = dir.magnitude;

        float l = new Vector3(dir.x, 0, dir.z).magnitude;

        float bigAngle = Mathf.Acos(l / distance) * Mathf.Rad2Deg;
        if (dir.y < 0) {
            bigAngle = -bigAngle;
        }

        if (distance > chainsLength[0] + chainsLength[1]) {
            chains[0].localEulerAngles = new Vector3(90 - bigAngle, 0, 0);
            chains[1].localEulerAngles = new Vector3(0, 0, 0);
        } else {
            float angle2 = CalcAngle(distance, chainsLength[0], chainsLength[1]);
            if (invert) { 
                angle2 = -angle2;
            }
            chains[0].localEulerAngles = new Vector3(90 - (bigAngle - angle2), 0, 0);

            float angle = CalcAngle(chainsLength[0], chainsLength[1], distance);
            if (invert) { 
                angle = -angle;
            }
            chains[1].localEulerAngles = new Vector3(-(180 - angle), 0, 0);
        }

        float angle3 = Mathf.Atan(dir.x / dir.z) * Mathf.Rad2Deg;
        if (dir.z < 0) {
            angle3 = 180+angle3;
        }
        root.localEulerAngles = new Vector3(0, angle3, 0);   
    }

    float CalcAngle(float a, float b, float c) {
        return Mathf.Acos((a*a + b*b - c*c) / (2 * a * b)) * Mathf.Rad2Deg;
    }

}
