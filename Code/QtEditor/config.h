#ifndef CONFIG_H
#define CONFIG_H

#define WINDOW_TITLE "Map Editor"

#define MAP_ID "map"

#define ASSETS_DIR "assets"
#define TILES_DIR "tiles"

#define OPEN_BTN_LABEL "Open"
#define SAVE_BTN_LABEL "Save"
#define RESET_BTN_LABEL "Reset"

#define WIDTH_FORM_LABEL "Width:"
#define HEIGHT_FORM_LABEL "Height:"

#define DEFAULT_GRID_WIDTH 3
#define DEFAULT_GRID_HEIGHT 3

#define TILE_OFFSET_X 64
#define TILE_OFFSET_Y 64

#define TILE_WIDTH 64
#define TILE_HEIGHT 64

#define TILE_CHOOSER_WIDTH 80
#define TILE_CHOOSER_HEIGHT 80

#define TEXTURE_LABEL "texture:"

#define TILE_TEMPLATE \
"\t\tTile {\n\
\t\t	T.Layer { texture: %1.texture }\n\
\n\
\t\t	behavior: %1.behavior\n\
\t\t}\n\n"

#define ROW_TEMPLATE \
"\tRow {\n\
%1\
\t}\n\n"

#define MAP_TEMPLATE \
"import QtQuick 2.0\n\
import gtg.map 1.4\n\
import gtg.tile 1.4 as T\n\
\n\
Map {\n\
	id: MAP_ID\n\
	tileSize: TILE_WIDTH\n\
\n\
%1\
}"

#endif
