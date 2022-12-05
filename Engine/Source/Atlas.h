#pragma once

#include <Aliases.h>
#include <Core/Logger.h>
#include <cstring>
namespace PetrolEngine {

    template<typename T>
    class Atlas {
    public:
        Atlas(int cellSize, int cellCountX, int cellCountY, const void* data = nullptr, uint64 size = 0): cellSize(cellSize), cellCountX(cellCountX), cellCountY(cellCountY) {
            this->data = new T[cellSize * cellSize * cellCountX * cellCountY]();

            if(size == 0) return;

            if(size != (cellSize * cellSize * cellCountX * cellCountY * sizeof(T))){
                LOG("Atlas data size is not correct", 3);
                LOG(toString(size) + " != " + toString(cellSize * cellSize * cellCountX * cellCountY * sizeof(T)), 3);
                return;
            }

            memcpy(this->data, data, size);
        }

        NO_DISCARD int getWidth () const { return cellSize * cellCountX; }
        NO_DISCARD int getHeight() const { return cellSize * cellCountY; }

        NO_DISCARD int getCellCountX() const { return cellCountX; }
        NO_DISCARD int getCellCountY() const { return cellCountY; }

        NO_DISCARD int getCellSize() const { return cellSize; }

        NO_DISCARD const T* getData() const { return data; }

        ~Atlas() { delete[] data; }

        NO_DISCARD constexpr uint64 getIndex(int x, int y, int cellX, int cellY, bool flipX = false, bool flipY = false) const {
            uint64 index = 0;

            index += cellSize * y * getWidth();
            index += cellSize * x;

            if(flipX) index += cellSize - 1;
            if(flipY) index += cellSize * getWidth() - getWidth();

            if(!flipX) index += cellX;
            if(!flipY) index += cellY*getWidth();

            if(flipX) index -= cellX;
            if(flipY) index -= cellY*getWidth();

            return index;
        }

        NO_DISCARD T* getCell(int x, int y, bool flipX = false, bool flipY = false) const {
            auto* cell = new T[cellSize * cellSize];

            for (int ix = 0; ix < cellSize; ix++) {
                for (int iy = 0; iy < cellSize; iy++) {
                    cell[iy * cellSize + ix] = data[getIndex(x, y, ix, iy, flipX, flipY)];
                }
            }

            return cell;
        }

        void setCell(const T* value, int x, int y, int w, int h, bool flipY = false) {
            if (w > cellSize || h > cellSize) { LOG("Cell is too big to fit into atlas.", 2); return; }

            for(int iy = 0; iy < cellSize; iy++)
                for(int ix = 0; ix < cellSize; ix++)
                    data[getIndex(x, y, ix, iy)] = (ix >= w || iy >= h) ? 0 : value[(flipY ? (h-iy-1) : (iy)) * w + ix];
        }

    private:
        T* data;

        int cellSize;
        int cellCountX;
        int cellCountY;
    };
}