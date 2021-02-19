#include <gpch.h>
#include <Gwafix\Shader.h>

#include <Gwafix\Util\FileHandler.h>
#include <glad\glad.h>

//gets the location of a uniform || make it store it later but for now just get the location
static inline int32_t Gwafix_Shader_GetUniformLocation(Gwafix_Shader_Shader* shader, const char* name)
{
	if (!shader)
	{
		LogData("Gwafix Warning: NULL Shader || Shader is NULL can not get uniform location of %s!\n", name);
		return -1;
	}

	int32_t loc = glGetUniformLocation(shader->id, name);
	if (loc == GL_INVALID_OPERATION)
		LogData("Gwafix Error: NULL Shader Uniform Location || Shader Uniform: %s could not be found in current bound Shader!\n", name);

	return loc;
}

//compiles a shader
static inline int32_t Gwafix_Shader_CompileShader(const char* source, uint32_t type)
{
	if (!source)
	{
		LogError("Shader NULL Source", "Failed to compile Shader source, source was NULL! Check filepath.");
		return -1;
	}

	uint32_t shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	//check if compiled
	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);

		switch (type)
		{

			//Vertex
		case GL_VERTEX_SHADER:
			LogError("Compile Error: Vertex Shader", infoLog);
			glDeleteShader(shader);
			return -1;

			//Fragment
		case GL_FRAGMENT_SHADER:
			LogError("Compile Error: Fragment Shader", infoLog);
			glDeleteShader(shader);
			return -1;

			//Geometry
		case GL_GEOMETRY_SHADER:
			LogError("Compile Error: Geometry Shader", infoLog);
			glDeleteShader(shader);
			return -1;

			//compute

			//invalid
		default:
			LogError("Compile Error: Null Shader", "Invalid Shader of none existent type");
			glDeleteShader(shader);
			return -1;
		}
	}

	return shader;
}

Gwafix_Shader_Shader* Gwafix_Shader_CreateVertex(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
	//read vertex and fragment path
	int32_t v = Gwafix_Shader_CompileShader(Gwafix_FileHander_ReadTextFile(vertexPath), GL_VERTEX_SHADER);
	if (v == -1)
	{
		//LogError("Vertex Shader Fail", "Failed to compile Vertex Shader!");
		return NULL;
	}

	int32_t f = Gwafix_Shader_CompileShader(Gwafix_FileHander_ReadTextFile(fragmentPath), GL_FRAGMENT_SHADER);
	if (f == -1)
	{
		//LogError("Vertex Shader Fail", "Failed to compile Fragment Shader!");
		return NULL;
	}

	int32_t g;
	if (geometryPath)
	{
		g = Gwafix_Shader_CompileShader(Gwafix_FileHander_ReadTextFile(geometryPath), GL_GEOMETRY_SHADER);
		if (g == -1)
			return NULL;
	}

	//make shader
	Gwafix_Shader_Shader* shader = malloc(sizeof(Gwafix_Shader_Shader));
	shader->id = glCreateProgram();
	glAttachShader(shader->id, v);
	glAttachShader(shader->id, f);
	if(geometryPath)
		glAttachShader(shader->id, g);
	glLinkProgram(shader->id);

	//clean
	glDeleteShader(v);
	glDeleteShader(f);
	if(geometryPath)
		glDeleteShader(g);

	//check if linked correctly
	int  success;
	char infoLog[512];
	glGetProgramiv(shader->id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader->id, 512, NULL, infoLog);
		LogError("Link Error: Shader Program", infoLog);
		glDeleteProgram(shader);
		free(shader);
		return NULL;
	}

	shader->type = Gwafix_ShaderType_Vertex;
	return shader;
}

Gwafix_Shader_Shader* Gwafix_Shader_CreateVertexSource(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{
	if (!vertexSource)
	{
		LogError("Vertex Shader Fail", "Vertex source was NULL!");
		return NULL;
	}

	if (!fragmentSource)
	{
		LogError("Vertex Shader Fail", "Fragment source was NULL!");
		return NULL;
	}

	//read vertex and fragment path
	int32_t v = Gwafix_Shader_CompileShader(vertexSource, GL_VERTEX_SHADER);
	if (v == -1)
	{
		//LogError("Vertex Shader Fail", "Failed to compile Vertex Shader!");
		return NULL;
	}

	int32_t f = Gwafix_Shader_CompileShader(fragmentSource, GL_FRAGMENT_SHADER);
	if (f == -1)
	{
		//LogError("Vertex Shader Fail", "Failed to compile Fragment Shader!");
		return NULL;
	}

	int32_t g;
	if (geometrySource)
	{
		g = Gwafix_Shader_CompileShader(geometrySource, GL_GEOMETRY_SHADER);
		if (g == -1)
			return NULL;
	}

	//make shader
	Gwafix_Shader_Shader* shader = malloc(sizeof(Gwafix_Shader_Shader));
	shader->id = glCreateProgram();
	glAttachShader(shader->id, v);
	glAttachShader(shader->id, f);
	if (geometrySource)
		glAttachShader(shader->id, g);
	glLinkProgram(shader->id);

	//clean
	glDeleteShader(v);
	glDeleteShader(f);
	if (geometrySource)
		glDeleteShader(g);

	//check if linked correctly
	int  success;
	char infoLog[512];
	glGetProgramiv(shader->id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader->id, 512, NULL, infoLog);
		LogError("Link Error: Shader Program", infoLog);
		glDeleteProgram(shader);
		free(shader);
		return NULL;
	}

	shader->type = Gwafix_ShaderType_Vertex;
	return shader;
}

void Gwafix_Shader_Destroy(Gwafix_Shader_Shader* shader)
{
	if (!shader)
	{
		LogError("Shader NULL", "Shader is NULL can not destroy!");
		return;
	}

	glDeleteProgram(shader->id);
	//clean seartched unforms
	free(shader);
	shader = NULL;
}

void Gwafix_Shader_Bind(Gwafix_Shader_Shader* shader)
{
	if (!shader)
	{
		LogError("Shader NULL", "Shader is NULL can not bind!");
		return;
	}

	glUseProgram(shader->id);
}

void Gwafix_Shader_Unbind(Gwafix_Shader_Shader* shader)
{
	//skip checking shader validity since it is not used in Opengl

	glUseProgram(shader->id);
}

void Gwafix_Shader_SetBool(Gwafix_Shader_Shader* shader, const char* name, bool value)
{
	glUniform1i(Gwafix_Shader_GetUniformLocation(shader, name), value);
}

void Gwafix_Shader_SetInt(Gwafix_Shader_Shader* shader, const char* name, int32_t value)
{
	glUniform1i(Gwafix_Shader_GetUniformLocation(shader, name), value);
}

void Gwafix_Shader_SetInt2(Gwafix_Shader_Shader* shader, const char* name, int32_t value1, int32_t value2)
{
	glUniform2i(Gwafix_Shader_GetUniformLocation(shader, name), value1, value2);
}

void Gwafix_Shader_SetInt3(Gwafix_Shader_Shader* shader, const char* name, int32_t value1, int32_t value2, int32_t value3)
{
	glUniform3i(Gwafix_Shader_GetUniformLocation(shader, name), value1, value2, value3);
}

void Gwafix_Shader_SetInt4(Gwafix_Shader_Shader* shader, const char* name, int32_t value1, int32_t value2, int32_t value3, int32_t value4)
{
	glUniform4i(Gwafix_Shader_GetUniformLocation(shader, name), value1, value2, value3, value4);
}

void Gwafix_Shader_SetIntVec2(Gwafix_Shader_Shader* shader, const char* name, int32_t* value)
{
	glUniform2iv(Gwafix_Shader_GetUniformLocation(shader, name), 2, value);
}

void Gwafix_Shader_SetIntVec3(Gwafix_Shader_Shader* shader, const char* name, int32_t* value)
{
	glUniform3iv(Gwafix_Shader_GetUniformLocation(shader, name), 3, value);
}

void Gwafix_Shader_SetIntVec4(Gwafix_Shader_Shader* shader, const char* name, int32_t* value)
{
	glUniform4iv(Gwafix_Shader_GetUniformLocation(shader, name), 4, value);
}

void Gwafix_Shader_SetUint(Gwafix_Shader_Shader* shader, const char* name, uint32_t value)
{
	glUniform1ui(Gwafix_Shader_GetUniformLocation(shader, name), value);
}

void Gwafix_Shader_SetUint2(Gwafix_Shader_Shader* shader, const char* name, uint32_t value1, uint32_t value2)
{
	glUniform2ui(Gwafix_Shader_GetUniformLocation(shader, name), value1, value2);
}

void Gwafix_Shader_SetUint3(Gwafix_Shader_Shader* shader, const char* name, uint32_t value1, uint32_t value2, uint32_t value3)
{
	glUniform3ui(Gwafix_Shader_GetUniformLocation(shader, name), value1, value2, value3);
}

void Gwafix_Shader_SetUint4(Gwafix_Shader_Shader* shader, const char* name, uint32_t value1, uint32_t value2, uint32_t value3, uint32_t value4)
{
	glUniform4ui(Gwafix_Shader_GetUniformLocation(shader, name), value1, value2, value3, value4);
}

void Gwafix_Shader_SetUintVec2(Gwafix_Shader_Shader* shader, const char* name, uint32_t* value)
{
	glUniform2uiv(Gwafix_Shader_GetUniformLocation(shader, name), 2, value);
}

void Gwafix_Shader_SetUintVec3(Gwafix_Shader_Shader* shader, const char* name, uint32_t* value)
{
	glUniform3uiv(Gwafix_Shader_GetUniformLocation(shader, name), 3, value);
}

void Gwafix_Shader_SetUintVec4(Gwafix_Shader_Shader* shader, const char* name, uint32_t* value)
{
	glUniform4uiv(Gwafix_Shader_GetUniformLocation(shader, name), 4, value);
}

void Gwafix_Shader_SetFloat(Gwafix_Shader_Shader* shader, const char* name, float value)
{
	glUniform1f(Gwafix_Shader_GetUniformLocation(shader, name), value);
}

void Gwafix_Shader_SetFloat2(Gwafix_Shader_Shader* shader, const char* name, float value1, float value2)
{
	glUniform2f(Gwafix_Shader_GetUniformLocation(shader, name), value1, value2);
}

void Gwafix_Shader_SetFloat3(Gwafix_Shader_Shader* shader, const char* name, float value1, float value2, float value3)
{
	glUniform3f(Gwafix_Shader_GetUniformLocation(shader, name), value1, value2, value3);
}

void Gwafix_Shader_SetFloat4(Gwafix_Shader_Shader* shader, const char* name, float value1, float value2, float value3, float value4)
{
	glUniform4f(Gwafix_Shader_GetUniformLocation(shader, name), value1, value2, value3, value4);
}

void Gwafix_Shader_SetVec2(Gwafix_Shader_Shader* shader, const char* name, float* value)
{
	glUniform2fv(Gwafix_Shader_GetUniformLocation(shader, name), 2, value);
}

void Gwafix_Shader_SetVec3(Gwafix_Shader_Shader* shader, const char* name, float* value)
{
	glUniform3fv(Gwafix_Shader_GetUniformLocation(shader, name), 3, value);
}

void Gwafix_Shader_SetVec4(Gwafix_Shader_Shader* shader, const char* name, float* value)
{
	glUniform4fv(Gwafix_Shader_GetUniformLocation(shader, name), 4, value);
}

void Gwafix_Shader_SetMat2(Gwafix_Shader_Shader* shader, const char* name, bool transpose, float* value)
{
	glUniformMatrix2fv(Gwafix_Shader_GetUniformLocation(shader, name), 1, transpose, value);
}

void Gwafix_Shader_SetMat3(Gwafix_Shader_Shader* shader, const char* name, bool transpose, float* value)
{
	glUniformMatrix3fv(Gwafix_Shader_GetUniformLocation(shader, name), 1, transpose, value);
}

void Gwafix_Shader_SetMat4(Gwafix_Shader_Shader* shader, const char* name, bool transpose, float* value)
{
	glUniformMatrix4fv(Gwafix_Shader_GetUniformLocation(shader, name), 1, transpose, value);
}