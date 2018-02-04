
#include <iostream>
#include "shader.h"
#include <cmath>
#include "observatoryBlackHoleShader.h"

#define _USE_MATH_DEFINES
#define toRadian(degree)    ((degree)*(M_PI/180.0f))
#define toDegree(radian)    ((radian)*(180.0f/PI))

using namespace std;

void observatoryBlackHoleShader_init(miState* state, struct observatoryBlackHoleShader *paras, miBoolean *inst_req) {

	if (!paras) {
        *inst_req = miTRUE;

		cout << "---------------------------------------------------------" << endl;
        cout << "    observatoryBlackHoleShader, compiled on " << __DATE__ << endl;
		cout << "    if you have any trouble about this shader, please send e-mail to mathleona@gmail.com" << endl;
        cout << "---------------------------------------------------------" << endl;
    }

}

miBoolean observatoryBlackHoleShader (
    miColor *result, miState *state, struct observatoryBlackHoleShader *params  )
{
	miScalar transparency = *mi_eval_scalar(&params->transparency);
	miScalar radius = *mi_eval_scalar(&params->radius);
	//miBoolean debug = 1;
	miBoolean debug = *mi_eval_boolean(&params->debug);
	//cout << "debug : " << debug << endl;

	if (debug == 1) {
		cout << "ray type : " << state->type;
		cout << "debug : " << debug << endl;
	}

	if ((state->type == 1)&&(state->parent->type == 0)) {
	//if ((state->type == 1)&&(state->parent->type == 0)) {

		miVector current = state->point;
		miVector origin = state->org;

		if (debug == 1) {
			cout << "current / origin : " << current.x << " / " << current.y << " / " << current.z << " | " << origin.x << " / " << origin.y << " / " << origin.z << endl;
		}

		miVector middle;
		middle.x = (current.x + origin.x) / 2.0f;
		middle.y = (current.y + origin.y) / 2.0f;
		middle.z = (current.z + origin.z) / 2.0f;
		
		if (debug == 1) {
			cout << "middle : " << middle.x << " / " << middle.y << " / " << middle.z << endl;
		}

		miScalar distance = sqrt(pow(middle.x - 0, 2.0f) + pow(middle.y - 0, 2.0f) + pow(middle.z - 0, 2.0f));

		if (debug == 1) {
			cout << "radius : " << radius << endl;
			cout << "distance : " << distance << endl;
		}

		miVector toCenter;
		toCenter.x = 0.0 - middle.x;
		toCenter.y = 0.0 - middle.y;
		toCenter.z = 0.0 - middle.z;
		mi_vector_normalize(&toCenter);

		if (debug == 1) {
			cout << "toCenter : " << toCenter.x << " / " << toCenter.y << " / " << toCenter.z << endl;
		}

		miVector toOrigin;
		toOrigin.x = state->point.x - state->org.x;
		toOrigin.y = state->point.y - state->org.y;
		toOrigin.z = state->point.z - state->org.z;

		//mi_vector_neg(&toOrigin);

		if (debug == 1) {
			cout << "neg toCenter : " << toCenter.x << " / " << toCenter.y << " / " << toCenter.z << endl;
		}

		miVector prod;
		mi_vector_prod(&prod, &toOrigin, &toCenter);
		mi_vector_normalize(&prod);

		if (debug == 1) {
			cout << "prod : " << prod.x << " / " << prod.y << " / " << prod.z << endl;
		}

		if (radius > distance) {
			result->r = 0.f;
			result->g = 0.f;
			result->b = 0.f;
			return miTRUE;
		}

		miScalar radianAngle = (2.0f * radius) / (distance);
		
		//radianAngle = radianAngle - ((2.0f * radius) / radius);
		//radianAngle = toRadian(radianAngle);

		//radianAngle = M_PI - radianAngle;

		//miScalar radianAngle = toRadian((M_PI / 2.0) - degree);

		//cout << "degree / radianAngle : " << degree << " / " << radianAngle << endl;
		if (debug == 1) {
			cout << "radianAngle : " << radianAngle << endl;
		}

		miVector newDir;
		miMatrix rotateMat;
		mi_matrix_rotate_axis(rotateMat, &prod, radianAngle);
		mi_vector_transform(&newDir, &toOrigin, rotateMat);
		mi_vector_normalize(&newDir);
		
//		newDir.x = 1.0f;
		//newDir.y = 0;
		//newDir.z = 0;

		state->point = middle;
		state->dir = newDir;

		if (debug == 1) {
			cout << "org / dir : " << state->org.x << " / " << state->org.y << " / " << state->org.z << " | " << newDir.x << " / " << newDir.y << " / " << newDir.z << endl;
		}

		/*
		newDir.x = (newDir.x + 1) / 2.0f;
		newDir.y = (newDir.y + 1) / 2.0f;
		newDir.z = (newDir.z + 1) / 2.0f;

		result->r = newDir.x;
		result->g = newDir.y;
		result->b = newDir.z;

		return miTRUE;
		*/

		//mi_trace_transparent (result, state);
		mi_trace_refraction(result, state, &newDir);

		if (debug == 1) {
			cout << "result : " << result->r << " / " << result->g << " / " << result->b << endl;
		}
	} else {
		if (debug == 1) {
			cout << "========================================================" << endl;
		}
		miVector current = state->point;
		miVector origin = state->org;

		if (debug == 1) {
			cout << "current / origin : " << current.x << " / " << current.y << " / " << current.z << " | " << origin.x << " / " << origin.y << " / " << origin.z << endl;
		}

		mi_trace_transparent (result, state);
	}
	//miColor opacity;
	/*
	opacity.r = 1.0 - transparency;
	opacity.g = 1.0 - transparency;
	opacity.b = 1.0 - transparency;
	opacity.a = 1.0 - transparency;
	*/
	//mi_opacity_set(state, &opacity);
	//result->r = result->r * opacity.r;
	//result->g = result->g * opacity.g;
	//result->b = result->b * opacity.b;
	//result->r = 1.0;
	//result->g = 0;
	//result->b = 0;
	return miTRUE;
}

miInteger observatoryBlackHoleShader_version(void) {
    return 1;
}
	    
void observatoryBlackHoleShader_exit(miState* state, struct observatoryBlackHoleShader* paras) {
}
