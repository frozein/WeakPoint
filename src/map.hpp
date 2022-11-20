struct AABB
{
	int minX, maxX;
	int minY, maxY;
};

#define MAP_W 32
#define MAP_H 18

class Map
{
public:
	enum class TileType : int
	{
		GRASS    = 0,
		DIRT     = 1,
		TRANS_L  = 2,
		TRANS_R  = 3,
		TRANS_T  = 4,
		TRANS_B  = 5,
		TRANS_LT = 6,
		TRANS_LB = 7,
		TRANS_RT = 8,
		TRANS_RB = 9
	};

	enum class PropType : int
	{
		NONE = 0,
		TREE = 1
	};

private:
	const int MAP_SRC_SIZE = 16;

	int w, h;
	TileType* tiles;
	PropType* props;
	int* rands;

public:
	int mapL, mapT;
	int tileSize;

	//note: free mem for _tiles and _props after constructing, it is copied
	Map(int w, int h, TileType* tiles, PropType* props, int screenW, int screenH);
	~Map();

	void render();

	void get_map_pos(int sX, int sY, int* wX, int* wY);
	bool aabb_at(int x, int y, AABB* aabb);
};