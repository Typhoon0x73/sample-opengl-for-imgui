#include "Shader.h"

using namespace Sample;

/**
 * @brief		�R���X�g���N�^
 */
Shader::Shader() 
: ResourceBase()
, id_(0)
, matVP_(-1)
, matModel_(-1) {
}

/**
 * @brief		�R���X�g���N�^
 * @param[in]	name	�V�F�[�_�[(���_�V�F�[�_�[/�t���O�����g�V�F�[�_�[�Ŗ��O�w��)
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
 * @brief		�R���X�g���N�^
 * @param[in]	vname	���_�V�F�[�_�[
 * @param[in]	fname	�t���O�����g�V�F�[�_�[
 */
Shader::Shader(const char* vname, const char* fname) 
: ResourceBase()
, id_(0)
, matVP_(-1)
, matModel_(-1) {
	Load(vname, fname);
}

/**
 * @brief		�f�X�g���N�^
 */
Shader::~Shader() {
	Release();
}

/**
 * @brief		�V�F�[�_�[�̃R���p�C������
 */
GLuint Shader::Compile(GLenum type, const char* name) {
	FILE* fp = fopen(name, "rb");
	if (!fp)
	{
		ERROR_LOG("�V�F�[�_�[" << name << "���J���܂���");
		return 0;
	}
	fseek(fp, 0, SEEK_END);
	const size_t length = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* buf = new char[length + 1];
	fread(buf, length, 1, fp);
	buf[length] = '\0';

	//�V�F�[�_�[�̃R���p�C��
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
			ERROR_LOG("�V�F�[�_�[�̃R���p�C���Ɏ��s...\n" << buf);
		}
		glDeleteShader(shader);
		delete[] buf;
		return 0;
	}
	delete[] buf;
	return shader;
}

/**
 * @brief		�V�F�[�_�[�̐���
 * @param[in]	vname	���_�V�F�[�_�[
 * @param[in]	fname	�t���O�����g�V�F�[�_�[
 * @return		true	��������
 *				false	�������s
 */
bool Shader::Load(const char* vname, const char* fname){
	//�V�F�[�_�[�̃R���p�C��
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
			ERROR_LOG("�V�F�[�_�[�̃����N�Ɏ��s...\n" << buf);
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
	INFO_LOG("�V�F�[�_�[" << name_ << "��ǂݍ���...");
	return true;
}

/**
 * @brief		�V�F�[�_�[�̗L����
 * @return		true	����
 *				false	���s
 */
bool Shader::Enable() {
	glUseProgram(id_);
	return true;
}

/**
 * @brief		�V�F�[�_�[�ւ̃p�����[�^�[�ݒ�
 */
bool Shader::BindTexture(GLuint no, GLuint id) {
	glBindTextureUnit(no, id);
	return true;
}

/**
 * @brief		�V�F�[�_�[�ւ̃p�����[�^�[�ݒ�
 */
bool Shader::BindSampler(GLuint no, GLuint id) {
	glBindSampler(no, id);
	return true;
}

/**
 * @brief		�V�F�[�_�[�ւ̃p�����[�^�[�ݒ�
 */
bool Shader::SetViewProjectionMatrix(const float* fv) {
	glUniformMatrix4fv(matVP_, 1, GL_FALSE, fv);
	return true;
}

/**
 * @brief		�V�F�[�_�[�ւ̃p�����[�^�[�ݒ�
 */
bool Shader::SetModelMatrix(const float* fv) {
	glUniformMatrix4fv(matModel_, 1, GL_FALSE, fv);
	return true;
}

/**
 * @brief		�V�F�[�_�[�p�����[�^�[�̃��P�[�V�����擾
 */
GLint Shader::GetUniformLocation(const char* name) {
	return glGetUniformLocation(id_, name);
}

/**
 * @brief		�������
 */
void Shader::Release() {
	if (id_ == 0)
	{
		return;
	}
	glDeleteProgram(id_);
	id_ = 0;
	INFO_LOG("�V�F�[�_�[" << name_ << "�����...");
	name_ = "";
}