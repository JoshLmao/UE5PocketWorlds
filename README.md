# UE5PocketWorlds

This repo contains an example project on how to use `CommonUI` and `PocketWorlds` plugins, found in Epic's [Lyra Sample Game](https://docs.unrealengine.com/5.0/en-US/lyra-sample-game-in-unreal-engine/)

The project has been updated from 5.1, and currently works and tested with Unreal Engine 5.5.4

![preview of repository and pocket world](./repo-media/repo-preview.gif)

## How to: CommonUI

For CommonUI to work, the project imports CommonGame and copied over functionality from Lyra class where needed.

## How to: PocketWorlds

Below is a TL;DR on how a pocket world is used

- Spawn PocketWorld on Start, StreamOut until ready to use
  - Done in `AUE5PocketWorldsPlayerController::InitInventoryPocketWorld()`
- Once Inventory opened, obtain level and StreamIn
  - In `UUW_PlayerRepresentation::NativeConstruct()`
- On Inventory closed, StreamOut level
  - In `UUW_CharacterRepresentation::NativeDestruct`
