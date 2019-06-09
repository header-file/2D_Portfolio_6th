#pragma once
class Animation;

class Image
{
	//이미지를 어디에서 로드하는가
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,   //리소스에서 리소드에 등록한 이미지를 등록, 리소스 아이디가 필요
		LOAD_FILE,       //파일로부터    
		LOAD_EMPTY,      //빈 비트맵으로부터
		LOAD_END,       //
	};
		
private:

	typedef struct tamImageInfo
	{

		DWORD   resID;
		HDC		hMemDC;
		HBITMAP	hBit, hOldBit;

		float   x, y;
		int     width;			//이미지 전체 넓이
		int     height;			//이미지 전체 높이
		
		int     currentFrameX;  //프레임 이미지 중에 현재 랜더링 순서인 X쪽 인덱스
		int     currentFrameY;  //프레임 이미지 중에 현재 랜더링 순서인 Y쪽 인덱스
		int     maxFrameX;      //X쪽의 마지막 인덱스
		int		maxFrameY;      //Y쪽의 마지막 인덱스
		int     frameWidth;     //프레임 이미지 한장의 넓이
		int     frameHeight;    //프레임 이미지 한장의 높이
		BYTE    loadType;
		RECT    boundingBox;    //이미지의 렉트를 구현, 이미지 정보가 단독으로 있을때 사용하는데 거의 
		
		//객체를 구현할 때 포인트와 렉트를 두개 만들고 포인트 정보로는 이동, 렉트 정보로는 충돌

		tamImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOldBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
			boundingBox = RectMake(0, 0, 0, 0);
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

	


private:
	LPIMAGE_INFO   _imageInfo;   // 이미지 정보 구조체
	TCHAR*         _fileName;    // 파일 이름
	bool		   _trans;       // 트랜스컬러 유무
	COLORREF	   _transColor;  // 키 컬러(제거할 색)
	BLENDFUNCTION  _blendFunc;
	LPIMAGE_INFO   _blendImage;

/*
	핸들 : 핸들도 자료형, 포인터로 접근 할 수 없게 핸들로 전달하는 개념?
	  
		  뭔가 만든 대상에 대해 간접적으로 API를 사용해서 접근하기 위한 일종의 KEY 값 API 가 데이터


	포인터 사용의 문제 : 메모리에 잘 못 접근하면 생김
*/


public:
	Image();
	~Image();

	// 빈비트맵 로딩용
	bool Init(int _width, int height); //빈 비트맵일 경우 사용할 함수
	
	// 파일로부터의 로딩용
	bool Init(const TCHAR* fileName, int width, int height, bool trans = false, COLORREF transColor = false);
	bool Init(const TCHAR* fileName, float x, float y, int width, int height, bool trans = false, COLORREF transColor = false);
	
	// 프레임 이미지 용 (움직이는 것처럼 표시하기위한 이미지들)
	bool Init(const TCHAR* fileName, float x, float y, int width, int height, int frameX, int frameY,
		bool trans = false, COLORREF transColor = false);
	bool Init(const TCHAR* fileName, int width, int height, int frameX, int frameY,
		bool trans = false, COLORREF transColor = false);

	//초기 트랜스 컬러 셋팅 후 바꾸고 싶은 경우가 생긴다면, 기타 상태 설정 용
	void SetTransColor(bool trans, COLORREF transColor);

	//정리용
	void Release();

	
	//일반 이미지 렌더용
	void Render(HDC hdc);	
	void Render(HDC hdc, int destX, int destY);
	void Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//루프 랜더
	void LoopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);

	//애니 랜더
	void AniRender(HDC hdc, int destX, int destY, Animation* ani);

	// 스프라이트 이미지 랜더용
	void FrameRender(HDC hdc, int destX, int destY);
	void FrameRender(HDC hdc, int destX, int destY, int currentframeX, int currentframeY);

	// 알파 랜더
	void AlphaRender(HDC hdc, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	//편의를 위한 기타 함수
	//inline 으로 사용하면 속도가 빠르다, 빠른 이유 함수를 호출할때 필요한 과정(점프, 복사, 할당 같은)을 건너뛰고 바로 실행이 되기에
	//빈번하게 사용될 클래스의 멤버 변수등에 사용, Get, Set 함수 같은거
	inline void   SetX(float x) { _imageInfo->x = x; }
	inline float  GetX() { return _imageInfo->x; }

	inline void   SetY(float y) { _imageInfo->y = y; }
	inline float  GetY() { return _imageInfo->y; }

	inline void SetCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline float GetCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ? _imageInfo->x + (_imageInfo->width / 2) : _imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float GetCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ? _imageInfo->y + (_imageInfo->height / 2) : _imageInfo->y + (_imageInfo->frameHeight / 2);
	}
	
	inline int GetWidth() { return _imageInfo->width; }
	inline int GetHeight() { return _imageInfo->height; }

	inline RECT BoundingBox()
	{
		RECT rc = { int(_imageInfo->x),
		int(_imageInfo->y),
		int(_imageInfo->frameWidth),
		int(_imageInfo->frameHeight) };

		return rc;
	}

	inline void SetFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;

		if (frameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	inline void SetFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;

		if (frameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	inline int GetMaxFrameX() {	return _imageInfo->maxFrameX; }
	inline int GetMaxFrameY() { return _imageInfo->maxFrameY; }

	inline int GetFrameX() { return _imageInfo->currentFrameX; }
	inline int GetFrameY() { return _imageInfo->currentFrameY; }

	inline int GetFrameWidth() { return _imageInfo->frameWidth; }
	inline int GetFrameHeight() { return _imageInfo->frameHeight; }

	inline POINT GetSize()      { return POINT{ _imageInfo->width, _imageInfo->height }; }
	inline POINT GetFrameSize() { return POINT{ _imageInfo->frameWidth, _imageInfo->frameHeight}; }
	inline POINT GetMaxFrame()  { return POINT{ _imageInfo->maxFrameX, _imageInfo->maxFrameY }; }

	inline HDC   GetMemDC()     { return _imageInfo->hMemDC; }
};

