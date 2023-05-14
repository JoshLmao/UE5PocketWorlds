# UE5PocketWorlds

This repo contains an example project on how to use `CommonUI` and `PocketWorlds` plugins, found in Epic's [Lyra Sample Game](https://docs.unrealengine.com/5.0/en-US/lyra-sample-game-in-unreal-engine/)

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
