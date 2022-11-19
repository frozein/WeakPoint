struct AABB
{
	int minX, maxX;
	int minY, maxY;
};

#define MAP_W 48
#define MAP_H 27

#define TILE_SIDE 80

class Map
{
public:
	enum class TileType
	{
		GRASS,
		DIRT,
		TRANS_L,
		TRANS_R,
		TRANS_T,
		TRANS_B,
		TRANS_LT,
		TRANS_LB,
		TRANS_RT,
		TRANS_RB
	};

	enum class PropType
	{
		TREE,
		NONE
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