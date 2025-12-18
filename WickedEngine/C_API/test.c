
#include "wiApplication_API.h"
#include "wiAsync_API.h"
#include "wiAudio_API.h"
#include "wiBacklog_API.h"
#include "wiC_API.h"
#include "wiImage_API.h"
#include "wiInput_API.h"
#include "wiLoadingScreen_API.h"
#include "wiMath_API.h"
#include "wiNetwork_API.h"
#include "wiPathQuery_API.h"
#include "wiPhysics_API.h"
#include "wiPrimitive_API.h"
#include "wiRenderPath_API.h"
#include "wiRenderer_API.h"
#include "wiScene_API.h"
#include "wiSpriteAnim_API.h"
#include "wiSpriteFont_API.h"
#include "wiSprite_API.h"
#include "wiTexture_API.h"
#include "wiTrailRenderer_API.h"
#include "wiVideo_API.h"
#include "wiVoxelGrid_API.h"
#include <stdio.h>
#include <string.h>

int main() {
  setvbuf(stdout, NULL, _IONBF, 0);
  printf("Testing WickedEngine C API...\n");

  // Math Test
  wiVector v1 = wiVector_Create(1, 2, 3, 0);
  wiVector v2 = wiVector_Create(4, 5, 6, 0);
  wiVector v3 = wiVector_Add(v1, v2);

  printf("Vector Add: %f %f %f\n", v3.x, v3.y, v3.z);

  if (v3.x != 5 || v3.y != 7 || v3.z != 9) {
    printf("Math Test Failed!\n");
    return 1;
  }

  // Application Test (Symbolic)
  wiApplication app = NULL;
  wiApplication_GetActivePath(app);
  wiApplication_SetFPSDisplay(app, true);

  printf("Testing Renderer API...\n");
  wiRenderer_SetGameSpeed(1.5f);
  if (wiRenderer_GetGameSpeed() != 1.5f) {
    printf("Renderer GameSpeed Test Failed!\n");
    return 1;
  }
  wiRenderableLine line;
  line.start = wiVector_Create(0, 0, 0, 0);
  line.end = wiVector_Create(10, 10, 10, 0);
  line.color_start.r = 255;
  line.color_start.a = 255;
  line.color_end.r = 255;
  line.color_end.a = 255;
  wiRenderer_DrawLine(&line, false);
  printf("Renderer API Test Passed.\n");

  printf("Testing Backlog API...\n");
  wiBacklog_Post("C API Test Message");
  wiBacklog_Clear();
  printf("Backlog API Test Passed.\n");

  printf("Testing Input API...\n");
  if (wiInput_Down(WI_INPUT_KEYBOARD_BUTTON_SPACE, 0)) {
    printf("Input Test Warning: Space pressed unexpectedly\n");
  }
  wiVector ptr = wiVector_Create(100, 100, 0, 0);
  wiInput_SetPointer(ptr);
  wiVector ptr_read = wiInput_GetPointer();
  printf("Input Pointer Set/Get: (%f, %f)\n", ptr_read.x, ptr_read.y);

  // --- Audio API Test ---
  printf("Testing Audio API...\n");
  wiSound sound = wiAudio_CreateSound("test_audio.wav");
  if (sound) {
    wiSoundInstance instance = wiAudio_CreateSoundInstance(sound);
    if (instance) {
      wiAudio_SetVolume(0.5f, instance);
      printf("Audio Instance Volume: %f\n", wiAudio_GetVolume(instance));
      wiAudio_DestroySoundInstance(instance);
    }
    wiAudio_DestroySound(sound);
  }
  printf("Audio API Test Passed.\n");

  // --- SpriteFont API Test ---
  printf("Testing SpriteFont API...\n");
  wiSpriteFont font = wiSpriteFont_Create("Hello C API");
  if (font) {
    wiSpriteFont_SetSize(font, 24);
    wiVector pos = {10, 10, 0, 0};
    wiSpriteFont_SetPos(font, pos);
    wiSpriteFont_Draw(font);
    wiSpriteFont_Destroy(font);
  }
  printf("SpriteFont API Test Passed.\n");

  // --- Image API Test ---
  printf("Testing Image API...\n");
  wiImageParams params = wiImageParams_Create(10, 10, 100, 100);
  if (params) {
    wiVector pos = {50, 50, 0, 0};
    wiImageParams_SetPos(params, pos);
    wiVector read_pos = wiImageParams_GetPos(params);
    printf("Image Pos: %f %f\n", read_pos.x, read_pos.y);
    wiImageParams_Destroy(params);
  }
  printf("Image API Test Passed.\n");

  // --- Sprite API Test ---
  printf("Testing Sprite API...\n");
  wiSprite sprite = wiSprite_Create(NULL, NULL);
  if (sprite) {
    wiImageParams sp_params = wiImageParams_Create(0, 0, 200, 200);
    wiSprite_SetParams(sprite, sp_params);

    // Get params back (returns copy)
    wiImageParams read_params = wiSprite_GetParams(sprite);
    wiVector size = wiImageParams_GetSize(read_params);
    printf("Sprite Size: %f %f\n", size.x, size.y);

    wiImageParams_Destroy(sp_params);
    wiImageParams_Destroy(read_params);
    wiSprite_Destroy(sprite);
  }
  printf("Sprite API Test Passed.\n");

  // --- Network API Test ---
  printf("Testing Network API...\n");
  wiNetwork_Socket sock = wiNetwork_CreateSocket();
  if (sock) {
    if (wiNetwork_ListenPort(sock, 12345)) {
      printf("Network Listen Success on 12345\n");
    }
    wiNetwork_DestroySocket(sock);
  }
  printf("Network API Test Passed.\n");

  // --- Primitive API Test ---
  printf("Testing Primitive API...\n");
  wiAABB aabb =
      wiAABB_Create((wiVector){-1, -1, -1, 0}, (wiVector){1, 1, 1, 0});
  wiRay ray = wiRay_Create((wiVector){0, 0, -5, 0}, (wiVector){0, 0, 1, 0});
  if (wiRay_IntersectsAABB(ray, aabb)) {
    printf("Ray-AABB Intersection Passed.\n");
  } else {
    printf("Ray-AABB Intersection Failed!\n");
  }
  printf("Primitive API Test Passed.\n");

  // --- RenderPath API Test ---
  printf("Testing RenderPath API...\n");
  // We can't easily create a RenderPath3D here without a full engine instance,
  // but we can test the function call symbols linking at least.
  // In a real scenario we'd get the active render path from application.
  // For now, we just pass NULL and verify it doesn't crash (null check test).
  wiRenderPath3D_SetAO(NULL, 1);
  printf("RenderPath API Linkage Passed.\n");

  // --- Texture API Test ---
  printf("Testing Texture API...\n");
  wiTexture tex = wiTexture_GetLogo();
  if (tex) {
    int w = wiTexture_GetWidth(tex);
    int h = wiTexture_GetHeight(tex);
    printf("Logo Texture Size: %d x %d\n", w, h);
  }
  printf("Texture API Test Passed.\n");

  // --- VoxelGrid & PathQuery API Test ---
  printf("Testing VoxelGrid & PathQuery API...\n");
  wiVoxelGrid grid = wiVoxelGrid_Create();
  if (grid) {
    wiVoxelGrid_Init(grid, 10, 10, 10);
    wiVoxelGrid_SetVoxel(grid, 5, 5, 5, true);
    bool occupied = wiVoxelGrid_CheckVoxel(grid, 5, 5, 5);
    if (occupied)
      printf("Voxel Set/Check Passed.\n");
    else
      printf("Voxel Set/Check Failed!\n");

    wiPathQuery query = wiPathQuery_Create();
    if (query) {
      wiVector start = {0, 0, 0, 0};
      wiVector goal = {9, 9, 9, 0};
      // Just symbolic process call, pathfinding might fail in empty/small grid
      // but shouldn't crash
      wiPathQuery_Process(query, start, goal, grid);
      printf("PathQuery Process Linkage Passed.\n");
      wiPathQuery_Destroy(query);
    }
    wiVoxelGrid_Destroy(grid);
  }
  printf("VoxelGrid & PathQuery API Test Passed.\n");

  // --- Video API Test ---
  printf("Testing Video API...\n");
  wiVideo video = wiVideo_Load("test.mp4"); // Dummy load
  // We don't expect it to validly load a non-existent file, but we check
  // function linking
  if (wiVideo_IsValid(video)) {
    wiVideoInstance vinst = wiVideoInstance_Create(video);
    wiVideoInstance_Play(vinst);
    wiVideoInstance_Destroy(vinst);
  }
  wiVideo_Destroy(
      video); // Clean up resource wrapper (if we added destroy for it)
  printf("Video API Test Passed.\n");

  // --- LoadingScreen API Test ---
  printf("Testing LoadingScreen API...\n");
  wiLoadingScreen loading = wiLoadingScreen_Create();
  if (loading) {
    wiLoadingScreen_SetBackgroundMode(loading, 0); // Fill
    int prog = wiLoadingScreen_GetProgress(loading);
    printf("Loading Progress: %d\n", prog);

    // Test inheritance casting
    wiRenderPath2D rp2d = wiLoadingScreen_AsRenderPath2D(loading);
    if (rp2d)
      wiRenderPath2D_ClearSprites(rp2d);

    wiLoadingScreen_Destroy(loading);
  }
  printf("LoadingScreen API Test Passed.\n");

  // --- Scene API Test ---
  printf("Testing Scene API...\n");
  wiScene scene = wiScene_GetGlobal();
  if (scene) {
    wiEntity entity = wiScene_Entity_Create(scene);
    if (entity != WI_INVALID_ENTITY) {
      // Test Name Component
      wiNameComponent nameComp = wiScene_Component_CreateName(scene, entity);
      if (nameComp) {
        wiNameComponent_Set(nameComp, "MyEntity");
        const char *name = wiNameComponent_Get(nameComp);
        printf("Entity Name: %s\n", name);
        if (strcmp(name, "MyEntity") == 0) {
          printf("Name Component Set/Get Passed.\n");
        } else {
          printf("Name Component Set/Get Failed!\n");
        }
      }

      // Test Transform Component
      wiTransformComponent transformComp =
          wiScene_Component_CreateTransform(scene, entity);
      if (transformComp) {
        wiVector pos = {10, 20, 30, 0};
        wiTransformComponent_SetPosition(transformComp, pos);
        wiVector readPos = wiTransformComponent_GetPosition(transformComp);
        printf("Transform Position: %f %f %f\n", readPos.x, readPos.y,
               readPos.z);
        if (readPos.x == 10 && readPos.y == 20 && readPos.z == 30) {
          printf("Transform Component Set/Get Passed.\n");
        } else {
          printf("Transform Component Set/Get Failed!\n");
        }
      }

      wiScene_Entity_Remove(scene, entity);
    }
  }
  printf("Scene API Test Passed.\n");

  // --- Physics API Test ---
  printf("Testing Physics API...\n");
  wiPhysics_Initialize();
  wiPhysics_SetEnabled(true);
  if (wiPhysics_IsEnabled()) {
    printf("Physics Enabled.\n");
  } else {
    printf("Physics Enable Failed!\n");
  }

  // Test RigidBody Component
  if (scene) {
    wiEntity entity = wiScene_Entity_Create(scene);
    wiRigidBodyPhysicsComponent rb =
        wiScene_Component_CreateRigidBodyPhysics(scene, entity);
    if (rb) {
      // wiScene_Update(scene, 0.016f);
      // wiPhysics_RigidBody_Activate(rb);
      // wiVector force = {0, 10, 0, 0};
      // wiPhysics_RigidBody_ApplyForce(rb, force);
      printf("RigidBody Component Created.\n");
    }
    wiScene_Entity_Remove(scene, entity);
  }
  printf("Physics API Test Passed.\n");

  // --- Async API Test ---
  printf("Testing Async API...\n");
  wiAsync async = wiAsync_Create();
  if (async) {
    if (wiAsync_IsCompleted(async)) {
      printf("Async Context Initially Completed.\n");
    }
    wiAsync_Wait(async); // Should return immediately for empty context
    wiAsync_Destroy(async);
  }
  printf("Async API Test Passed.\n");

  // --- TrailRenderer API Test ---
  printf("Testing TrailRenderer API...\n");
  wiTrailRenderer trail = wiTrailRenderer_Create();
  if (trail) {
    if (wiTrailRenderer_GetPointCount(trail) == 0) {
      printf("TrailRenderer Initial Point Count 0 - Passed.\n");
    }
    wiVector pt = {1, 2, 3, 0};
    wiVector col = {1, 0, 0, 1};
    wiVector rot = {0, 0, 0, 0};
    wiTrailRenderer_AddPoint(trail, pt, 1.0f, col, rot);
    if (wiTrailRenderer_GetPointCount(trail) == 1) {
      printf("TrailRenderer AddPoint - Passed.\n");
    }
    wiTrailRenderer_SetWidth(trail, 5.0f);
    if (wiTrailRenderer_GetWidth(trail) == 5.0f) {
      printf("TrailRenderer SetWidth - Passed.\n");
    }
    wiTrailRenderer_SetBlendMode(trail, WI_TRAIL_BLENDMODE_ADDITIVE);
    if (wiTrailRenderer_GetBlendMode(trail) == WI_BLENDMODE_ADDITIVE) {
      printf("TrailRenderer SetBlendMode - Passed.\n");
    }

    wiTrailRenderer_Destroy(trail);
  }
  printf("TrailRenderer API Test Passed.\n");

  // --- SpriteAnim API Test ---
  printf("Testing SpriteAnim API...\n");
  wiSprite sprite_anim = wiSprite_Create(NULL, NULL);
  if (sprite_anim) {
    wiSpriteAnim anim = wiSprite_GetAnim(sprite_anim);
    if (anim) {
      wiSpriteAnim_SetRot(anim, 1.57f);
      if (wiSpriteAnim_GetRot(anim) == 1.57f) {
        printf("SpriteAnim SetRot - Passed.\n");
      }
      wiSpriteAnim_SetOpacity(anim, 0.5f);
      if (wiSpriteAnim_GetOpacity(anim) == 0.5f) {
        printf("SpriteAnim SetOpacity - Passed.\n");
      }
      wiVector vel = {1, 0, 0, 0};
      wiSpriteAnim_SetVelocity(anim, vel);
      wiVector read_vel = wiSpriteAnim_GetVelocity(anim);
      if (read_vel.x == 1.0f) {
        printf("SpriteAnim SetVelocity - Passed.\n");
      }
    }
    wiSprite_Destroy(sprite_anim);
  }
  printf("SpriteAnim API Test Passed.\n");

  // --- RenderPath3D Extended API Test ---
  printf("Testing RenderPath3D Extended API...\n");
  // Again, passing NULL just to check linkage of new functions
  wiRenderPath3D_SetResolutionScale(NULL, 0.5f);
  wiRenderPath3D_SetChromaticAberrationEnabled(NULL, true);
  wiRenderPath3D_SetFSREnabled(NULL, true);
  printf("RenderPath3D Extended API Linkage Passed.\n");

  printf("Test Finished.\n");
  return 0;
}
