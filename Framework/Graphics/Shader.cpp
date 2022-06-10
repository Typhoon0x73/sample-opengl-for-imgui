#include "Shader.h"

using namespace Sample;

/**
 * @brief		コンストラクタ
 */
Shader::Shader() 
: ResourceBase()
, id_(0)
, matVP_(-1)
, matModel_(-1) {
}

/**
 * @brief		コンストラクタ
 * @param[in]	name	シェーダー(頂点シェーダー/フラグメントシェーダーで名前指定)
 */
Shader::Shader(const char* name)
: ResourceBase()
, id_(0)
, matVP_(-1)
, matModel_(-1) {
	std::string tstr = name;
	size_t pos = tstr.find("/", 0);
	std::string vname = tstr.substr(0, pos);
	std::string fname = tstr.substr(pos + 1, tstr.length() - pos);
	Load(vname.c_str(), fname.c_str());
}
/**
 * @brief		コンストラクタ
 * @param[in]	vname	頂点シェーダー
 * @param[in]	fname	フラグメントシェーダー
 */
Shader::Shader(const char* vname, const char* fname) 
: ResourceBase()
, id_(0)
, matVP_(-1)
, matModel_(-1) {
	Load(vname, fname);
}

/**
 * @brief		デストラクタ
 */
Shader::~Shader() {
	Release();
}

/**
 * @brief		シェーダーのコンパイル命令
 */
GLuint Shader::Compile(GLenum type, const char* name) {
	FILE* fp = fopen(name, "rb");
	if (!fp)
	{
		ERROR_LOG("シェーダー" << name << "が開けません");
		return 0;
	}
	fseek(fp, 0, SEEK_END);
	const size_t length = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* buf = new char[length + 1];
	fread(buf, length, 1, fp);
	buf[length] = '\0';

	//シェーダーのコンパイル
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &buf, nullptr);
	glCompileShader(shader);
	GLint compiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		GLint info = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info);
		if (info > 0)
		{
			char* buf = new char[info];
			glGetShaderInfoLog(shader, info, NULL, buf);
			ERROR_LOG("シェーダーのコンパイルに失敗...\n" << buf);
		}
		glDeleteShader(shader);
		delete[] buf;
		return 0;
	}
	delete[] buf;
	return shader;
}

/**
 * @brief		シェーダーの生成
 * @param[in]	vname	頂点シェーダー
 * @param[in]	fname	フラグメントシェーダー
 * @return		true	生成成功
 *				false	生成失敗
 */
bool Shader::Load(const char* vname, const char* fname){
	//シェーダーのコンパイル
	GLuint vs = Compile(GL_VERTEX_SHADER, vname);
	GLuint fs = Compile(GL_FRAGMENT_SHADER, fname);
	if (!vs || !fs)
	{
		return false;
	}
	id_ = glCreateProgram();
	glAttachShader(id_, fs);
	glDeleteShader(fs);
	glAttachShader(id_, vs);
	glDeleteShader(vs);
	glLinkProgram(id_);
	GLint linkStatus = GL_FALSE;
	glGetProgramiv(id_, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE)
	{
		GLint info = 0;
		glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &info);
		if (info > 0)
		{
			char* buf = new char[info];
			glGetProgramInfoLog(id_, info, NULL, buf);
			ERROR_LOG("シェーダーのリンクに失敗...\n" << buf);
		}
		glDeleteProgram(id_);
		return false;
	}

	glUseProgram(id_);
	matVP_ = GetUniformLocation("matVP");
	matModel_ = GetUniformLocation("matModel");
	GLint texColor = GetUniformLocation("texColor");
	glUniform1i(texColor, 0);
	glUseProgram(0);

	name_ = vname;
	name_ += "/";
	name_ += fname;
	INFO_LOG("シェーダー" << name_ << "を読み込み...");
	return true;
}

/**
 * @brief		シェーダーの有効化
 * @return		true	成功
 *				false	失敗
 */
bool Shader::Enable() {
	glUseProgram(id_);
	return true;
}

/**
 * @brief		シェーダーへのパラメーター設定
 */
bool Shader::BindTexture(GLuint no, GLuint id) {
	glBindTextureUnit(no, id);
	return true;
}

/**
 * @brief		シェーダーへのパラメーター設定
 */
bool Shader::BindSampler(GLuint no, GLuint id) {
	glBindSampler(no, id);
	return true;
}

/**
 * @brief		シェーダーへのパラメーター設定
 */
bool Shader::SetViewProjectionMatrix(const float* fv) {
	glUniformMatrix4fv(matVP_, 1, GL_FALSE, fv);
	return true;
}

/**
 * @brief		シェーダーへのパラメーター設定
 */
bool Shader::SetModelMatrix(const float* fv) {
	glUniformMatrix4fv(matModel_, 1, GL_FALSE, fv);
	return true;
}

/**
 * @brief		シェーダーパラメーターのロケーション取得
 */
GLint Shader::GetUniformLocation(const char* name) {
	return glGetUniformLocation(id_, name);
}

/**
 * @brief		解放処理
 */
void Shader::Release() {
	if (id_ == 0)
	{
		return;
	}
	glDeleteProgram(id_);
	id_ = 0;
	INFO_LOG("シェーダー" << name_ << "を解放...");
	name_ = "";
}