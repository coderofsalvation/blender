/*
 * $Id$
 *
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software  Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) 2006 by Nicholas Bishop
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): none yet.
 *
 * ***** END GPL LICENSE BLOCK *****
 */ 

#ifndef BDR_SCULPTMODE_H
#define BDR_SCULPTMODE_H

#include "DNA_listBase.h"
#include "DNA_vec_types.h"
#include "DNA_key_types.h"

#include "BLI_pbvh.h"

struct bContext;
struct KeyBlock;
struct Object;
struct Scene;
struct PBVHNode;
struct SculptUndoNode;

int sculpt_poll(struct bContext *C);
void sculpt_update_mesh_elements(struct Scene *scene, struct Object *ob, int need_fmap);

/* Undo */

typedef struct SculptUndoNode {
	struct SculptUndoNode *next, *prev;

	char idname[MAX_ID_NAME];	/* name instead of pointer*/
	void *node;					/* only during push, not valid afterwards! */

	float (*co)[3];
	short (*no)[3];
	int totvert;

	/* non-multires */
	int maxvert;				/* to verify if totvert it still the same */
	int *index;					/* to restore into right location */

	/* multires */
	int maxgrid;				/* same for grid */
	int gridsize;				/* same for grid */
	int totgrid;				/* to restore into right location */
	int *grids;					/* to restore into right location */

	/* layer brush */
	float *layer_disp;
 
	/* paint mask */
	float *pmask;
	int pmask_layer_offset;

	/* shape keys */
	char *shapeName[32]; /* keep size in sync with keyblock dna */
} SculptUndoNode;

SculptUndoNode *sculpt_undo_push_node(struct Object *ob, PBVHNode *node);
SculptUndoNode *sculpt_undo_get_node(struct PBVHNode *node);
void sculpt_undo_push_begin(char *name);
void sculpt_undo_push_end(void);

struct MultiresModifierData *sculpt_multires_active(struct Scene *scene, struct Object *ob);
int sculpt_modifiers_active(struct Scene *scene, struct Object *ob);
void sculpt_vertcos_to_key(struct Object *ob, struct KeyBlock *kb, float (*vertCos)[3]);

void brush_jitter_pos(struct Brush *brush, float *pos, float *jitterpos);

#endif
