#ifndef CONFIG_H
#define CONFIG_H

#define WINDOW_TITLE "Map Editor"

#define MAP_ID "map"

#define ASSETS_DIR "assets"
#define TILES_DIR ASSETS_DIR"/definitions/tiles"
#define IMAGES_DIR ASSETS_DIR"/images"

#define OPEN_BTN_LABEL "Open"
#define SAVE_BTN_LABEL "Save"

#define WIDTH_FORM_LABEL "Width:"
#define HEIGHT_FORM_LABEL "Height:"

#define WARNING_TITLE "Warning"

#define WARNING_EXIT "You have unsaved changes. Are you sure you want to exit?"

#define DEFAULT_GRID_WIDTH 3
#define DEFAULT_GRID_HEIGHT 3

#define TILE_OFFSET_X 64
#define TILE_OFFSET_Y 64

#define TILE_WIDTH 64
#define TILE_HEIGHT 64

#define TILE_CHOOSER_WIDTH 80
#define TILE_CHOOSER_HEIGHT 80

#define TEXTURE_LABEL "texture:"

#define PSTRINGIFY(a) #a
#define STRINGIFY(a) PSTRINGIFY(a)

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
	id: " MAP_ID "\n\
	tileSize: " STRINGIFY(TILE_WIDTH) "\n\
\n\
%1\
}"

#endif
