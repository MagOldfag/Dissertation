using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using RootMotion.FinalIK;

public class LookAt : MonoBehaviour
{
    CCDIK ik;
    // Start is called before the first frame update
    void Start()
    {
        ik = transform.parent.GetComponent<CCDIK>();   
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 pos = ik.solver.target.position;
        Vector3 dir = pos - transform.position;
        
        float angle3 = Mathf.Atan(dir.x / dir.z) * Mathf.Rad2Deg;
        if (dir.z < 0) {
            angle3 = 180+angle3;
        }
        transform.localEulerAngles = new Vector3(0, angle3, 0);  
    }
}
