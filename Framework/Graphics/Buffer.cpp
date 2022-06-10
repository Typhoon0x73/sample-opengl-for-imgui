#include "Buffer.h"

using namespace Sample;

/**
 * @brief		コンストラクタ
 */
Buffer::Buffer()
: id_(0) 
, type_(0) {
}

/**
 * @brief		デストラクタ
 */
Buffer::~Buffer() {
	glDeleteBuffers(1, &id_);
}

/**
 * @brief		バッファの生成
 * @param[in]	type	バッファの種類
 * @param[in]	size	バッファサイズ
 * @param[in]	data	バッファに格納するデータ
 * @param[in]	usage	バッファの使用法
 * @return		true	生成成功
 *				false	生成失敗
 */
bool Buffer::Create(GLenum type, GLsizeiptr size, const GLvoid* data, GLenum usage) {
	type_ = type;
	glGenBuffers(1, &id_);
	glBindBuffer(type_, id_);
	glBufferData(type_, size, data, usage);
	glBindBuffer(type_, 0);
	GL_ERROR_RETURN("バッファの作成に失敗...", false);
	return true;
}

/**
 * @brief		バッファへのデータ書き込み
 * @param[in]	offset	書き込みオフセット
 * @param[in]	size	書き込みサイズ
 * @param[in]	data	バッファに格納するデータ
 * @return		true	書き込み成功
 *				false	書き込み失敗
 */
bool Buffer::SubData(GLintptr offset, GLsizeiptr size, const GLvoid* data) {
	glBindBuffer(type_, id_);
	glBufferSubData(type_, offset, size, data);
	glBindBuffer(type_, 0);
	GL_ERROR_RETURN("バッファへのデータ転送に失敗...", false);
	return true;
}
