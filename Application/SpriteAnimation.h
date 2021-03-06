#ifndef SPRITEANIMATION_H_
#define SPRITEANIMATION_H_

#include <vector>
#include <string>
#include <utility>
#include <cstdint>

// --------------------------------------------------------------------------------
/// <summary>
/// スプライトアニメーションクラス
/// </summary>
// --------------------------------------------------------------------------------
class SpriteAnimation
{
public:

	// --------------------------------------------------------------------------------
	/// <summary>
	/// パターン構造体
	/// </summary>
	// --------------------------------------------------------------------------------
	struct Pattern
	{
		std::int32_t        m_ImageNo         {  -1 };     //!< 画像番号
		std::int32_t        m_OffsetX         {   0 };     //!< オフセットX
		std::int32_t        m_OffsetY         {   0 };     //!< オフセットY
		std::int32_t        m_Width           {   0 };     //!< 横幅
		std::int32_t        m_Height          {   0 };     //!< 高さ
		double              m_RefreshTime     { 0.0 };     //!< 描画時間(単位は秒)
		std::int32_t        m_DrawOffsetX     {   0 };     //!< 描画オフセットX
		std::int32_t        m_DrawOffsetY     {   0 };     //!< 描画オフセットY

		// ********************************************************************************
		/// <summary>
		/// コンストラクタ
		/// </summary>
		// ********************************************************************************
		explicit Pattern() = default;

		// ********************************************************************************
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="copy">コピーデータ</param>
		// ********************************************************************************
		explicit Pattern(const SpriteAnimation::Pattern& copy);

		// ********************************************************************************
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="move">ムーブデータ</param>
		// ********************************************************************************
		explicit Pattern(SpriteAnimation::Pattern&& move);

		// ********************************************************************************
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="n">画像番号</param>
		/// <param name="x">オフセットX</param>
		/// <param name="y">オフセットY</param>
		/// <param name="w">横幅</param>
		/// <param name="h">高さ</param>
		/// <param name="t">描画時間(単位は秒)</param>
		/// <param name="ox">描画オフセットX</param>
		/// <param name="oy">描画オフセットY</param>
		// ********************************************************************************
		explicit Pattern(std::int32_t n, std::int32_t x, std::int32_t y,
			std::int32_t w, std::int32_t h, double t, std::int32_t ox, std::int32_t oy);

		// ********************************************************************************
		/// <summary>
		/// operator= 代入演算
		/// </summary>
		/// <param name="copy">コピーデータ</param>
		/// <returns>*this</returns>
		// ********************************************************************************
		SpriteAnimation::Pattern& operator=(const SpriteAnimation::Pattern& copy);

		// ********************************************************************************
		/// <summary>
		/// operator= 代入演算
		/// </summary>
		/// <param name="move">ムーブデータ</param>
		/// <returns>*this</returns>
		// ********************************************************************************
		SpriteAnimation::Pattern& operator=(SpriteAnimation::Pattern&& move);

		// ********************************************************************************
		/// <summary>
		/// operator== 等価比較演算
		/// </summary>
		/// <param name="pattern">比較対象</param>
		/// <returns>true : パターンデータ一致, false : 一致しない</returns>
		// ********************************************************************************
		bool operator==(const SpriteAnimation::Pattern& pattern) const;

		// ********************************************************************************
		/// <summary>
		/// operator!= 比較演算
		/// </summary>
		/// <param name="pattern">比較対象</param>
		/// <returns>!(*this == pattern)</returns>
		// ********************************************************************************
		bool operator!=(const SpriteAnimation::Pattern& pattern) const;
	};

public:

	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	// ********************************************************************************
	explicit SpriteAnimation() = default;

	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="copy">コピーデータ</param>
	// ********************************************************************************
	explicit SpriteAnimation(const SpriteAnimation& copy);

	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="move">ムーブデータ</param>
	// ********************************************************************************
	explicit SpriteAnimation(SpriteAnimation&& move);

	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="patterns">パターン配列</param>
	/// <param name="hasLooped">ループフラグ</param>
	// ********************************************************************************
	explicit SpriteAnimation(const std::vector<SpriteAnimation::Pattern>& patterns, bool hasLooped);
	
	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="patterns">パターン配列(ムーブ)</param>
	/// <param name="hasLooped">ループフラグ</param>
	// ********************************************************************************
	explicit SpriteAnimation(std::vector<SpriteAnimation::Pattern>&& patterns, bool hasLooped);

	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="patterns">パターン配列</param>
	/// <param name="count">パターン登録数</param>
	/// <param name="hasLooped">ループフラグ</param>
	// ********************************************************************************
	explicit SpriteAnimation(SpriteAnimation::Pattern* patterns, std::size_t count, bool hasLooped);
	
	// ********************************************************************************
	/// <summary>
	/// デストラクタ
	/// </summary>
	// ********************************************************************************
	virtual ~SpriteAnimation();

	// ********************************************************************************
	/// <summary>
	/// アニメーションの更新
	/// </summary>
	/// <param name="deltaTime">更新時間(単位は秒)</param>
	/// <returns>true : 更新あり, false : 更新なし</returns>
	// ********************************************************************************
	bool update(const float deltaTime);

	// ********************************************************************************
	/// <summary>
	/// パターンデータの追加
	/// </summary>
	/// <param name="pattern">追加するパターンデータ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool addPattern(const SpriteAnimation::Pattern& pattern);

	// ********************************************************************************
	/// <summary>
	/// パターンデータの追加
	/// </summary>
	/// <param name="pattern">追加するパターンデータ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool addPattern(SpriteAnimation::Pattern&& pattern);

	// ********************************************************************************
	/// <summary>
	/// パターンデータの変更
	/// </summary>
	/// <param name="no">変更する配列番号</param>
	/// <param name="pattern">変更後のパターンデータ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool setPattern(std::size_t no, const SpriteAnimation::Pattern& pattern);

	// ********************************************************************************
	/// <summary>
	/// パターンデータの変更
	/// </summary>
	/// <param name="no">変更する配列番号</param>
	/// <param name="pattern">変更後のパターンデータ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool setPattern(std::size_t no, SpriteAnimation::Pattern&& pattern);

	// ********************************************************************************
	/// <summary>
	/// パターンデータの削除
	/// </summary>
	/// <param name="no">削除する配列番号</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool removePattern(std::size_t no);

	// ********************************************************************************
	/// <summary>
	/// パターンデータの削除
	/// </summary>
	/// <param name="pattern">削除するパターンデータ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool removePattern(const SpriteAnimation::Pattern& pattern);

	// ********************************************************************************
	/// <summary>
	/// パターンデータの削除
	/// </summary>
	/// <param name="pattern">削除するパターンデータのイテレータ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool removePattern(std::vector<SpriteAnimation::Pattern>::const_iterator pattern);

	// ********************************************************************************
	/// <summary>
	/// パターンデータの全削除
	/// </summary>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool clear();

	// ********************************************************************************
	/// <summary>
	/// パターン配列の変更
	/// </summary>
	/// <param name="patterns">変更後のパターン配列</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool setPatternArray(const std::vector<SpriteAnimation::Pattern>& patterns);

	// ********************************************************************************
	/// <summary>
	/// パターン配列の変更
	/// </summary>
	/// <param name="patterns">変更後のパターン配列</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool setPatternArray(std::vector<SpriteAnimation::Pattern>&& patterns);

	// ********************************************************************************
	/// <summary>
	/// パターン配列の変更
	/// </summary>
	/// <param name="patterns">変更後のパターン配列</param>
	/// <param name="count">変更後のパターン数</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool setPatternArray(SpriteAnimation::Pattern* patterns, std::size_t count);

	// ********************************************************************************
	/// <summary>
	/// アニメーションのループ設定
	/// </summary>
	/// <param name="hasLooped">true : ループする, false : ループしない</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool setLoop(bool hasLooped);

	// ********************************************************************************
	/// <summary>
	/// 再生中パターン番号の変更
	/// </summary>
	/// <param name="no">変更後のパターン番号</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool setCurrentPatternNo(std::int32_t no);

	// ********************************************************************************
	/// <summary>
	/// 時間指定による再生中パターン番号の変更
	/// </summary>
	/// <param name="t">再生したいアニメーション経過時間(単位は秒)</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool setCurrentPatternNoByTime(double t);

	// ********************************************************************************
	/// <summary>
	/// パターンアニメーションの再生
	/// </summary>
	/// <param name="no">再生開始パターン番号</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool play(std::size_t no = 0);

	// ********************************************************************************
	/// <summary>
	/// 開始時間指定によるパターンアニメーションの再生
	/// </summary>
	/// <param name="t">再生開始アニメーション時間(単位は秒)</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool playByTime(double t = 0.0);
	
	// ********************************************************************************
	/// <summary>
	/// パターン配列の取得
	/// </summary>
	/// <returns>パターン配列ポインタ, nullptr : データなし</returns>
	// ********************************************************************************
	const std::vector<SpriteAnimation::Pattern>* const patternArray() const;

	// ********************************************************************************
	/// <summary>
	/// パターン配列の取得
	/// </summary>
	/// <returns>パターン配列ポインタ, nullptr : データなし</returns>
	// ********************************************************************************
	std::vector<SpriteAnimation::Pattern>* const patternArray();

	// ********************************************************************************
	/// <summary>
	/// 時間指定によるパターンデータの取得
	/// </summary>
	/// <param name="t">取得したいアニメーション時間(単位は秒)</param>
	/// <returns>指定された時間に再生されるパターンデータポインタ, nullptr : データなし</returns>
	// ********************************************************************************
	const SpriteAnimation::Pattern* const patternByTime(double t) const;

	// ********************************************************************************
	/// <summary>
	/// 時間指定によるパターンデータの取得
	/// </summary>
	/// <param name="t">取得したいアニメーション時間(単位は秒)</param>
	/// <returns>指定された時間に再生されるパターンデータポインタ, nullptr : データなし</returns>
	// ********************************************************************************
	SpriteAnimation::Pattern* const patternByTime(double t);

	// ********************************************************************************
	/// <summary>
	/// パターンデータの取得
	/// </summary>
	/// <param name="no">取得したい配列番号</param>
	/// <returns>パターンデータポインタ, nullptr : データなし</returns>
	// ********************************************************************************
	const SpriteAnimation::Pattern* const patternByArrayNo(std::size_t no) const;

	// ********************************************************************************
	/// <summary>
	/// パターンデータの取得
	/// </summary>
	/// <param name="no">取得したい配列番号</param>
	/// <returns>パターンデータポインタ, nullptr : データなし</returns>
	// ********************************************************************************
	SpriteAnimation::Pattern* const patternByArrayNo(std::size_t no);

	// ********************************************************************************
	/// <summary>
	/// 再生中のパターンデータの取得
	/// </summary>
	/// <returns>再生中のパターンデータポインタ, nullptr : データなし</returns>
	// ********************************************************************************
	const SpriteAnimation::Pattern* const currentPattern() const;

	// ********************************************************************************
	/// <summary>
	/// 再生中のパターンデータの取得
	/// </summary>
	/// <returns>再生中のパターンデータポインタ, nullptr : データなし</returns>
	// ********************************************************************************
	SpriteAnimation::Pattern* const currentPattern();

	// ********************************************************************************
	/// <summary>
	/// ループ設定の確認
	/// </summary>
	/// <returns>true : ループする, false : ループしない</returns>
	// ********************************************************************************
	bool hasLooped() const;

	// ********************************************************************************
	/// <summary>
	/// アニメーションが終了しているか判定(ループフラグが立っていれば必ずfalseが返る)
	/// </summary>
	/// <returns>true : アニメーション終了, false : アニメーション中</returns>
	// ********************************************************************************
	bool hasEnded() const;

	// ********************************************************************************
	/// <summary>
	/// 時間指定によるパターン番号の取得
	/// </summary>
	/// <param name="t">取得したい時間</param>
	/// <returns>指定された時間に再生されるパターン番号</returns>
	// ********************************************************************************
	std::int32_t patternNoByTime(double t) const;

	// ********************************************************************************
	/// <summary>
	/// 再生中のパターン番号の取得
	/// </summary>
	/// <returns>再生中のパターン番号, -1 : データなし</returns>
	// ********************************************************************************
	std::int32_t currentPatternNo() const;

	// ********************************************************************************
	/// <summary>
	/// パターン変更用タイマーの取得
	/// </summary>
	/// <returns>パターン毎の経過時間(単位は秒)</returns>
	// ********************************************************************************
	double timer() const;

	// ********************************************************************************
	/// <summary>
	/// アニメーション終了までの合計時間の取得(ループ関係なく配列の合計描画時間が返る)
	/// </summary>
	/// <returns>アニメーション終了までの合計時間(単位は秒)</returns>
	// ********************************************************************************
	double totalTime() const;

	// ********************************************************************************
	/// <summary>
	/// operator= 代入演算
	/// </summary>
	/// <param name="copy">コピーデータ</param>
	/// <returns>*this</returns>
	// ********************************************************************************
	SpriteAnimation& operator=(const SpriteAnimation& copy);

	// ********************************************************************************
	/// <summary>
	/// operator= 代入演算
	/// </summary>
	/// <param name="move">ムーブデータ</param>
	/// <returns>*this</returns>
	// ********************************************************************************
	SpriteAnimation& operator=(SpriteAnimation&& move);

	// ********************************************************************************
	/// <summary>
	/// operator== 等価比較演算
	/// </summary>
	/// <param name="animation">比較対象</param>
	/// <returns>true : アニメーションデータ一致, false : 一致しない</returns>
	// ********************************************************************************
	bool operator==(const SpriteAnimation& animation) const;

	// ********************************************************************************
	/// <summary>
	/// operator!= 比較演算
	/// </summary>
	/// <param name="animation">比較演算</param>
	/// <returns>!(*this == animation)</returns>
	// ********************************************************************************
	bool operator!=(const SpriteAnimation& animation) const;

private:

	// ********************************************************************************
	/// <summary>
	/// 内部で再生中のパターン番号を丸める処理
	/// </summary>
	// ********************************************************************************
	void roundCurrentPatternNo();

	std::vector<Pattern>     m_PatternArray         {     0 };     //!< パターン配列
	bool                     m_hasLooped            { false };	   //!< ループフラグ
	std::int32_t             m_CurrentPatternNo     {    -1 };	   //!< 再生中のパターン番号
	double                   m_Timer                {   0.0 };	   //!< 再生中のパターン更新用タイマー
	double                   m_TotalTime            {   0.0 };	   //!< アニメーション終了までの合計時間

};

//--------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
/// <summary>
/// スプライトアニメーション管理クラス
/// </summary>
// --------------------------------------------------------------------------------
class SpriteAnimationController
{
public:

	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	// ********************************************************************************
	explicit SpriteAnimationController() = default;

	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="copy">コピーデータ</param>
	// ********************************************************************************
	explicit SpriteAnimationController(const SpriteAnimationController& copy);

	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="move">ムーブデータ</param>
	// ********************************************************************************
	explicit SpriteAnimationController(SpriteAnimationController&& move);

	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pFile">.saファイルパス</param>
	/// <param name="outTexturePathArray">出力先画像ファイルパス配列</param>
	// ********************************************************************************
	explicit SpriteAnimationController(const char* pFile, std::vector<std::string>* outTexturePathArray);

	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pData">.saデータ</param>
	/// <param name="dataLen">データ長</param>
	/// <param name="outTexturePathArray">出力先画像ファイルパス配列</param>
	// ********************************************************************************
	explicit SpriteAnimationController(const char* pData, std::size_t dataLen, std::vector<std::string>* outTexturePathArray);
	
	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="animations">アニメーション配列</param>
	// ********************************************************************************
	explicit SpriteAnimationController(const std::vector<std::pair<std::string, SpriteAnimation>>& animations);

	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="animations">アニメーション配列</param>
	// ********************************************************************************
	explicit SpriteAnimationController(std::vector<std::pair<std::string, SpriteAnimation>>&& animations);

	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="animations">アニメーション配列</param>
	/// <param name="count">アニメーション数</param>
	// ********************************************************************************
	explicit SpriteAnimationController(std::pair<std::string, SpriteAnimation>* animations, std::size_t count);
	
	// ********************************************************************************
	/// <summary>
	/// デストラクタ
	/// </summary>
	// ********************************************************************************
	virtual ~SpriteAnimationController();

	// ********************************************************************************
	/// <summary>
	/// アニメーションの更新
	/// </summary>
	/// <param name="deltaTime">更新時間(単位は秒)</param>
	/// <returns>true : 更新あり, false : 更新なし</returns>
	// ********************************************************************************
	bool update(const float deltaTime);
	
	// ********************************************************************************
	/// <summary>
	/// アニメーションデータの追加
	/// </summary>
	/// <param name="name">アニメーション名</param>
	/// <param name="animation">アニメーションデータ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool addAnimation(const std::string& name, const SpriteAnimation& animation);

	// ********************************************************************************
	/// <summary>
	/// アニメーションデータの追加
	/// </summary>
	/// <param name="name">アニメーション名</param>
	/// <param name="animation">アニメーションデータ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool addAnimation(const std::string& name, SpriteAnimation&& animation);

	// ********************************************************************************
	/// <summary>
	/// アニメーションデータの追加
	/// </summary>
	/// <param name="name">アニメーション名</param>
	/// <param name="animation">アニメーションデータ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool addAnimation(std::string&& name, const SpriteAnimation& animation);

	// ********************************************************************************
	/// <summary>
	/// アニメーションデータの追加
	/// </summary>
	/// <param name="name">アニメーション名</param>
	/// <param name="animation">アニメーションデータ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool addAnimation(std::string&& name, SpriteAnimation&& animation);

	// ********************************************************************************
	/// <summary>
	/// アニメーションデータの追加
	/// </summary>
	/// <param name="animation">アニメーション配列</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool addAnimation(const std::pair<std::string, SpriteAnimation>& animation);

	// ********************************************************************************
	/// <summary>
	/// アニメーションデータの追加
	/// </summary>
	/// <param name="animation">アニメーション配列</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool addAnimation(std::pair<std::string, SpriteAnimation>&& animation);

	// ********************************************************************************
	/// <summary>
	/// アニメーション名の変更
	/// </summary>
	/// <param name="no">変更するアニメーション配列番号</param>
	/// <param name="name">変更後の名前</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool setAnimationName(std::size_t no, const std::string& name);

	// ********************************************************************************
	/// <summary>
	/// アニメーション名の変更
	/// </summary>
	/// <param name="no">変更するアニメーション配列番号</param>
	/// <param name="name">変更後の名前</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool setAnimationName(std::size_t no, std::string&& name);

	// ********************************************************************************
	/// <summary>
	/// アニメーションデータの変更
	/// </summary>
	/// <param name="no">変更するアニメーション配列番号</param>
	/// <param name="animation">変更後のアニメーションデータ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool setAnimation(std::size_t no, const SpriteAnimation& animation);

	// ********************************************************************************
	/// <summary>
	/// アニメーションデータの変更
	/// </summary>
	/// <param name="no">変更するアニメーション配列番号</param>
	/// <param name="animation">変更後のアニメーションデータ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool setAnimation(std::size_t no, SpriteAnimation&& animation);

	// ********************************************************************************
	/// <summary>
	/// アニメーションデータの変更
	/// </summary>
	/// <param name="no">変更するアニメーション配列番号</param>
	/// <param name="name">変更後の名前</param>
	/// <param name="animation">変更後のアニメーションデータ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool setAnimation(std::size_t no, const std::string& name, const SpriteAnimation& animation);

	// ********************************************************************************
	/// <summary>
	/// アニメーションデータの変更
	/// </summary>
	/// <param name="no">変更するアニメーション配列番号</param>
	/// <param name="name">変更後の名前</param>
	/// <param name="animation">変更後のアニメーションデータ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool setAnimation(std::size_t no, const std::string& name, SpriteAnimation&& animation);

	// ********************************************************************************
	/// <summary>
	/// アニメーションデータの変更
	/// </summary>
	/// <param name="no">変更するアニメーション配列番号</param>
	/// <param name="name">変更後の名前</param>
	/// <param name="animation">変更後のアニメーションデータ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool setAnimation(std::size_t no, std::string&& name, const SpriteAnimation& animation);

	// ********************************************************************************
	/// <summary>
	/// アニメーションデータの変更
	/// </summary>
	/// <param name="no">変更するアニメーション配列番号</param>
	/// <param name="name">変更後の名前</param>
	/// <param name="animation">変更後のアニメーションデータ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool setAnimation(std::size_t no, std::string&& name, SpriteAnimation&& animation);

	// ********************************************************************************
	/// <summary>
	/// アニメーションデータの変更
	/// </summary>
	/// <param name="no">変更するアニメーション配列番号</param>
	/// <param name="animation">変更後のアニメーションデータ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool setAnimation(std::size_t no, const std::pair<std::string, SpriteAnimation>& animation);

	// ********************************************************************************
	/// <summary>
	/// アニメーションデータの変更
	/// </summary>
	/// <param name="no">変更するアニメーション配列番号</param>
	/// <param name="animation">変更後のアニメーションデータ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool setAnimation(std::size_t no, std::pair<std::string, SpriteAnimation>&& animation);
	
	// ********************************************************************************
	/// <summary>
	/// アニメーションデータの削除
	/// </summary>
	/// <param name="no">削除するアニメーション配列番号</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool removeAnimation(std::size_t no);

	// ********************************************************************************
	/// <summary>
	/// 名前指定でアニメーションデータの削除(同一名はすべて削除)
	/// </summary>
	/// <param name="name">削除するアニメーション名</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool removeAnimation(const std::string& name);

	// ********************************************************************************
	/// <summary>
	/// アニメーションデータ指定でアニメーションデータの削除(同一データはすべて削除)
	/// </summary>
	/// <param name="animation">削除するアニメーションデータ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool removeAnimation(const SpriteAnimation& animation);

	// ********************************************************************************
	/// <summary>
	/// [key, data]でアニメーションデータの削除(同一データはすべて削除)
	/// </summary>
	/// <param name="name">削除するアニメーション名</param>
	/// <param name="animation">削除するアニメーションデータ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool removeAnimation(const std::string& name, SpriteAnimation& animation);

	// ********************************************************************************
	/// <summary>
	/// アニメーションデータ指定でアニメーションデータの削除(同一データはすべて削除)
	/// </summary>
	/// <param name="animation">削除するアニメーションデータ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool removeAnimation(const std::pair<std::string, SpriteAnimation>& animation);

	// ********************************************************************************
	/// <summary>
	/// イテレータ指定でアニメーションデータの削除
	/// </summary>
	/// <param name="animation">削除するアニメーションデータイテレータ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool removeAnimation(std::vector<std::pair<std::string, SpriteAnimation>>::const_iterator animation);
	
	// ********************************************************************************
	/// <summary>
	/// アニメーションデータの全削除
	/// </summary>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool clear();

	// ********************************************************************************
	/// <summary>
	/// アニメーション配列の変更
	/// </summary>
	/// <param name="animations">変更後のアニメーション配列</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool setAnimation(const std::vector<std::pair<std::string, SpriteAnimation>>& animations);

	// ********************************************************************************
	/// <summary>
	/// アニメーション配列の変更
	/// </summary>
	/// <param name="animations">変更後のアニメーション配列</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool setAnimation(std::vector<std::pair<std::string, SpriteAnimation>>&& animations);

	// ********************************************************************************
	/// <summary>
	/// アニメーション配列の変更
	/// </summary>
	/// <param name="animations">変更後のアニメーション配列</param>
	/// <param name="count">変更後のアニメーション数</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool setAnimation(std::pair<std::string, SpriteAnimation>* animations, std::size_t count);

	// ********************************************************************************
	/// <summary>
	/// 再生アニメーションの変更
	/// </summary>
	/// <param name="key">変更後のアニメーション番号</param>
	/// <param name="isSamed">再生中のアニメーションと同一で上書きしないフラグ(false指定で同一アニメーションでも0から再生)</param>
	/// <returns>true : 変更あり, false : 変更なし</returns>
	// ********************************************************************************
	bool changeAnimation(std::size_t key, bool isSamed = true);

	// ********************************************************************************
	/// <summary>
	/// 名前指定で再生アニメーションの変更(同一名が複数ある場合最初のアニメーションになる)
	/// </summary>
	/// <param name="key">変更後のアニメーション名</param>
	/// <param name="isSamed">再生中のアニメーションと同一で上書きしないフラグ(false指定で同一アニメーションでも0から再生)</param>
	/// <returns>true : 変更あり, false : 変更なし</returns>
	// ********************************************************************************
	bool changeAnimation(const std::string& key, bool isSamed = true);

	// ********************************************************************************
	/// <summary>
	/// アニメーション配列の取得
	/// </summary>
	/// <returns>アニメーション配列, nullptr : データなし</returns>
	// ********************************************************************************
	const std::vector<std::pair<std::string, SpriteAnimation>>* const animationArray() const;

	// ********************************************************************************
	/// <summary>
	/// アニメーション配列の取得
	/// </summary>
	/// <returns>アニメーション配列, nullptr : データなし</returns>
	// ********************************************************************************
	std::vector<std::pair<std::string, SpriteAnimation>>* const animationArray();

	// ********************************************************************************
	/// <summary>
	/// 再生中のアニメーションデータの取得
	/// </summary>
	/// <returns>再生中のアニメーションデータ, nullptr : データなし</returns>
	// ********************************************************************************
	const SpriteAnimation* const currentAnimation() const;

	// ********************************************************************************
	/// <summary>
	/// 再生中のアニメーションデータの取得
	/// </summary>
	/// <returns>再生中のアニメーションデータ, nullptr : データなし</returns>
	// ********************************************************************************
	SpriteAnimation* const currentAnimation();

	// ********************************************************************************
	/// <summary>
	/// 再生中のパターンデータの取得
	/// </summary>
	/// <returns>再生中のパターンデータ, nullptr : データなし</returns>
	// ********************************************************************************
	const SpriteAnimation::Pattern* const currentPattern() const;

	// ********************************************************************************
	/// <summary>
	/// 再生中のパターンデータの取得
	/// </summary>
	/// <returns>再生中のパターンデータ, nullptr : データなし</returns>
	// ********************************************************************************
	SpriteAnimation::Pattern* const currentPattern();

	// ********************************************************************************
	/// <summary>
	/// 再生中のアニメーション名の取得
	/// </summary>
	/// <returns>再生中のアニメーション名, nullptr : データなし</returns>
	// ********************************************************************************
	const std::string* const currentAnimationName() const;

	// ********************************************************************************
	/// <summary>
	/// 再生中のアニメーション番号の取得
	/// </summary>
	/// <returns>再生中のアニメーション番号, -1 : データなし</returns>
	// ********************************************************************************
	std::int32_t currentAnimationNo() const;

	// ********************************************************************************
	/// <summary>
	/// アニメーション数の取得
	/// </summary>
	/// <returns>アニメーション数</returns>
	// ********************************************************************************
	std::size_t animationCount() const;

	// ********************************************************************************
	/// <summary>
	/// operator= 代入演算
	/// </summary>
	/// <param name="copy">コピーデータ</param>
	/// <returns>*this</returns>
	// ********************************************************************************
	SpriteAnimationController& operator=(const SpriteAnimationController& copy);

	// ********************************************************************************
	/// <summary>
	/// operator= 代入演算
	/// </summary>
	/// <param name="move">ムーブデータ</param>
	/// <returns>*this</returns>
	// ********************************************************************************
	SpriteAnimationController& operator=(SpriteAnimationController&& move);

	// ********************************************************************************
	/// <summary>
	/// operator== 等価比較演算
	/// </summary>
	/// <param name="controller">比較対象</param>
	/// <returns>true : 一致, false : 一致しない</returns>
	// ********************************************************************************
	bool operator==(const SpriteAnimationController& controller) const;

	// ********************************************************************************
	/// <summary>
	/// operator!= 比較演算
	/// </summary>
	/// <param name="controller">比較対象</param>
	/// <returns>!(*this == controller)</returns>
	// ********************************************************************************
	bool operator!=(const SpriteAnimationController& controller) const;

private:

	// ********************************************************************************
	/// <summary>
	/// 内部で再生中のアニメーション番号を丸める処理
	/// </summary>
	// ********************************************************************************
	void roundCurrentAnimationNo();

	std::vector<std::pair<std::string, SpriteAnimation>>     m_AnimationArray         {  0 };     //!< アニメーション配列
	std::int32_t                                             m_CurrentAnimationNo     { -1 };     //!< 再生中のアニメーション番号
};

//--------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
/// <summary>
/// .saデータからアニメーション管理クラス,画像パス配列に分解するクラス
/// </summary>
// --------------------------------------------------------------------------------
class SpriteAnimationDataParser
{
public:

	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pData">データ</param>
	/// <param name="dataLen">データ長</param>
	// ********************************************************************************
	explicit SpriteAnimationDataParser(const char* pData, std::size_t dataLen);

	// ********************************************************************************
	/// <summary>
	/// デストラクタ
	/// </summary>
	// ********************************************************************************
	virtual ~SpriteAnimationDataParser();

	// ********************************************************************************
	/// <summary>
	/// 解析、分解
	/// </summary>
	/// <param name="outAnimation">出力先</param>
	/// <param name="outTexturePathArray">出力先</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool parseFromSA(SpriteAnimationController* outAnimation, std::vector<std::string>* outTexturePathArray);

private:

	// ********************************************************************************
	/// <summary>
	/// アニメーション情報の解析、分解
	/// </summary>
	/// <param name="out">出力先</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool animationParse(SpriteAnimationController* out);

	// ********************************************************************************
	/// <summary>
	/// パターン情報の解析、分解
	/// </summary>
	/// <param name="out">出力先</param>
	/// <param name="index">アニメーション情報データインデックス</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool patternParse(SpriteAnimationController * out, std::int32_t& index);

	// ********************************************************************************
	/// <summary>
	/// 画像パス配列情報の解析、分解
	/// </summary>
	/// <param name="out">出力先</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool texturePathArrayParse(std::vector<std::string>* out);

	// ********************************************************************************
	/// <summary>
	/// データ配列の先頭から4バイト分を4バイトデータに変換
	/// </summary>
	/// <param name="pData">データ配列</param>
	/// <returns>4バイトデータ</returns>
	// ********************************************************************************
	std::int32_t charToNum(const char* pData);

	const char*     m_pData            ;     //!< .saデータ
	std::size_t     m_DataLen     { 0 };     //!< データ長
	std::size_t     m_Index       { 0 };     //!< 操作インデックス
};

//--------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
/// <summary>
/// .saファイルに出力するクラス
/// </summary>
// --------------------------------------------------------------------------------
class SpriteAnimationDataExporter
{
public:

	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pName">出力ファイルパス</param>
	// ********************************************************************************
	explicit SpriteAnimationDataExporter(const char* pName);

	// ********************************************************************************
	/// <summary>
	/// デストラクタ
	/// </summary>
	// ********************************************************************************
	virtual ~SpriteAnimationDataExporter();

	// ********************************************************************************
	/// <summary>
	/// .saデータに出力
	/// </summary>
	/// <param name="expoortController">出力するアニメーションデータ</param>
	/// <param name="exportTexturePathArray">出力する画像パス配列データ</param>
	/// <returns>true : 成功, false : 失敗</returns>
	// ********************************************************************************
	bool exportToSA(SpriteAnimationController* expoortController, std::vector<std::string>* exportTexturePathArray);

private:

	const char*     m_pFileName;     //!< 出力ファイルパス
};

#endif // !SPRITEANIMATION_H_
