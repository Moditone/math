//
//  bin_packing_space.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef DSPERADOS_GEOMETRY_BIN_PACKING_SPACE_HPP
#define DSPERADOS_GEOMETRY_BIN_PACKING_SPACE_HPP

#include <array>
#include <cassert>
#include <memory>

#include "rectangular.hpp"
#include "size.hpp"

namespace math
{
	//! Two-dimendional rectangular bin-packing algorithm
	/*! Allocate rectangles in an allocated space, stacking them
        as efficiently as possible.
     
        Based on http://www.blackpawn.com/texts/lightmaps/default.html */
	class BinPackingSpace
	{
	public:
		//! Create a bin-packing space of a given size
        BinPackingSpace(const Size2i& size) :
            root(size)
        {
            
        }
		
		//! Insert a rectangle of a given size inside the space.
		/*! @return nullptr if there was no space left */
        Rectanglei* insert(const Size2i& size)
        {
            return root.insert(size);
        }
		
		//! Return the size of this space
		const Size2i& getSize() const { return root.bounds.size; }
		
	private:
		//! Used to represent a node inside the space
		struct Node
		{
		public:
			//! Construct the node of a given size
            Node(const Rectanglei& bounds) : bounds(bounds) { }
			
			//! Insert a rectangle into this node
			/*! @return nullptr if there was no space */
			Rectanglei* insert(const Size2i& size)
            {
                if (children.first != nullptr)
                {
                    // Is there room in the first child?
                    const auto result = children.first->insert(size);
                    if (result)
                        return result;
                    
                    // Is there room in the second child?
                    assert(children.second != nullptr);
                    return children.second->insert(size);
                } else {
                    if (taken)
                        return nullptr;
                    
                    if (bounds.size.width < size.width || bounds.size.height < size.height)
                        return nullptr;
                    
                    // Size2 is perfect!
                    if (bounds.size == size)
                    {
                        taken = true;
                        return &bounds;
                    }
                    
                    // Decide which way to split
                    auto deltaWidth = bounds.size.width - size.width;
                    auto deltaHeight = bounds.size.height - size.height;
                    
                    // Split up
                    if (deltaWidth > deltaHeight)
                    {
                        children.first = std::make_unique<Node>(Rectanglei(bounds.origin, Size2i(bounds.size.width - deltaWidth, bounds.size.height)));
                        children.second = std::make_unique<Node>(Rectanglei({bounds.origin.x + size.width, bounds.origin.y}, Size2i(deltaWidth, bounds.size.height)));
                    } else {
                        children.first = std::make_unique<Node>(Rectanglei(bounds.origin, Size2i(bounds.size.width, bounds.size.height - deltaHeight)));
                        children.second = std::make_unique<Node>(Rectanglei({bounds.origin.x, bounds.origin.y + size.height}, Size2i(bounds.size.width, deltaHeight)));
                    }
                    
                    return children.first->insert(size);
                }
                
                return nullptr;
            }
			
		public:
			//! The children of this node
			/*! If this node is a leaf, the children are nullptrs */
			std::pair<std::unique_ptr<Node>, std::unique_ptr<Node>> children;
			
			//! The bounds of this node
			Rectanglei bounds;
			
			//! Is this node taken?
			/*! Taken nodes are always end-leafs */
			bool taken = false;
		};
		
	private:
		//! The one-and-only root node
		Node root;
	};
}

#endif
