# RewindSystemUE
Object rewind system for Unreal Engine 5.2 and C++ with multiplayer support

Instructions:

-All actors that are going to be rewindable must have the RewineableActorComponent.
  
  *You must configure how often the actor's transform will be saved for rewinding, the maximum amount of transform that will be saved and the rewinding speed. 
 
  NOTE: The shorter the save time and the greater the maximum amount of transform, the more fluid the movement will be.

-The actors (for example the player) who are going to do the rewind must have the RewineableActorComponent and call the Server_StartRewind function.
For example: <code>RewindActorComponent->Server_StartRewind();</code>
