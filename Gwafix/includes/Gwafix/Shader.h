//defines a genaric Shader implementation

#ifndef Shader_h
#define Shader_h

#ifdef __cplusplus

extern "C" {
#endif

#include <stdint.h>

	//defines the shader types
	typedef enum
	{
		Gwafix_ShaderType_Vertex = 0x01,
		Gwafix_ShaderType_Compute = 0x02
		//Gwafix_ShaderType_Geometry = 0x02,
		//Gwafix_ShaderType_Compute = 0x04

	} Gwafix_Shader_ShaderType;

	//defines a shader
	typedef struct
	{
		uint32_t id;
		//seartched uniforms
		uint8_t type : 2; //0b00000000

	} Gwafix_Shader_Shader;

	//creates a vertex Shader
	Gwafix_Shader_Shader* Gwafix_Shader_CreateVertex(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
	//creates a vertex Shader from source
	Gwafix_Shader_Shader* Gwafix_Shader_CreateVertexSource(const char* vertexSource, const char* fragmentSource, const char* geometrySource);
	//creates a compute Shader
	//Gwafix_Shader_Shader* Gwafix_Shader_CreateCompute(const char* computePath);
	//destroys a Shader
	void Gwafix_Shader_Destroy(Gwafix_Shader_Shader* shader);

	//binds a Shader
	void Gwafix_Shader_Bind(Gwafix_Shader_Shader* shader);
	//unbinds a Shader
	void Gwafix_Shader_Unbind(Gwafix_Shader_Shader* shader);

	//pass a bool unform
	void Gwafix_Shader_SetBool(Gwafix_Shader_Shader* shader, const char* name, bool value);

	//pass a int1 uniform
	void Gwafix_Shader_SetInt(Gwafix_Shader_Shader* shader, const char* name, int32_t value);
	//pass a int2 uniform || expects a 2 element array
	void Gwafix_Shader_SetInt2(Gwafix_Shader_Shader* shader, const char* name, int32_t value1, int32_t value2);
	//pass a int3 uniform || expects a 3 element array
	void Gwafix_Shader_SetInt3(Gwafix_Shader_Shader* shader, const char* name, int32_t value1, int32_t value2, int32_t value3);
	//pass a int4 uniform || expects a 4 element array
	void Gwafix_Shader_SetInt4(Gwafix_Shader_Shader* shader, const char* name, int32_t value1, int32_t value2, int32_t value3, int32_t value4);

	//pass a int vec2 uniform || expects a 2 element array
	void Gwafix_Shader_SetIntVec2(Gwafix_Shader_Shader* shader, const char* name, int32_t* value);
	//pass a int vec3 uniform || expects a 3 element array
	void Gwafix_Shader_SetIntVec3(Gwafix_Shader_Shader* shader, const char* name, int32_t* value);
	//pass a int vec4 uniform || expects a 4 element array
	void Gwafix_Shader_SetIntVec4(Gwafix_Shader_Shader* shader, const char* name, int32_t* value);

	//pass a uint1 uniform
	void Gwafix_Shader_SetUint(Gwafix_Shader_Shader* shader, const char* name, uint32_t value);
	//pass a uint2 uniform 
	void Gwafix_Shader_SetUint2(Gwafix_Shader_Shader* shader, const char* name, uint32_t value1, uint32_t value2);
	//pass a uint3 uniform 
	void Gwafix_Shader_SetUint3(Gwafix_Shader_Shader* shader, const char* name, uint32_t value1, uint32_t value2, uint32_t value3);
	//pass a uint4 uniform 
	void Gwafix_Shader_SetUint4(Gwafix_Shader_Shader* shader, const char* name, uint32_t value1, uint32_t value2, uint32_t value3, uint32_t value4);

	//pass a uint vec2 uniform || expects a 2 element array
	void Gwafix_Shader_SetUintVec2(Gwafix_Shader_Shader* shader, const char* name, uint32_t* value);
	//pass a uint vec3 uniform || expects a 3 element array
	void Gwafix_Shader_SetUintVec3(Gwafix_Shader_Shader* shader, const char* name, uint32_t* value);
	//pass a uint vec4 uniform || expects a 4 element array
	void Gwafix_Shader_SetUintVec4(Gwafix_Shader_Shader* shader, const char* name, uint32_t* value);

	//pass a float1 uniform
	void Gwafix_Shader_SetFloat(Gwafix_Shader_Shader* shader, const char* name, float value);
	//pass a float2 uniform
	void Gwafix_Shader_SetFloat2(Gwafix_Shader_Shader* shader, const char* name, float value1, float value2);
	//pass a float3 uniform 
	void Gwafix_Shader_SetFloat3(Gwafix_Shader_Shader* shader, const char* name, float value1, float value2, float value3);
	//pass a float4 uniform 
	void Gwafix_Shader_SetFloat4(Gwafix_Shader_Shader* shader, const char* name, float value1, float value2, float value3, float value4);

	//pass a float vec2 uniform || expects a 2 element array
	void Gwafix_Shader_SetVec2(Gwafix_Shader_Shader* shader, const char* name, float* value);
	//pass a float vec3 uniform || expects a 3 element array
	void Gwafix_Shader_SetVec3(Gwafix_Shader_Shader* shader, const char* name, float* value);
	//pass a float vec4 uniform || expects a 4 element array
	void Gwafix_Shader_SetVec4(Gwafix_Shader_Shader* shader, const char* name, float* value);

	//pass a mat2 uniform || expects a 2 element array
	void Gwafix_Shader_SetMat2(Gwafix_Shader_Shader* shader, const char* name, bool transpose, float* value);
	//pass a mat3 uniform || expects a 3 element array
	void Gwafix_Shader_SetMat3(Gwafix_Shader_Shader* shader, const char* name, bool transpose, float* value);
	//pass a mat4 uniform || expects a 4 element array
	void Gwafix_Shader_SetMat4(Gwafix_Shader_Shader* shader, const char* name, bool transpose, float* value);

#ifdef __cplusplus

}
#endif

#endif