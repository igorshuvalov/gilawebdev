README
======

Use this module to add various hooks to extend functionalities of other contributed or core modules.


TWEAKS & HOOKS
==============

1. hook_fboauth_user_save()
---------------------------
   This hook is implemented to by-pass admin approval for users connecting through facebook.
   Similar functionality was achievable by:
     a. Using Facebook Rules and FBOauth in conjunction.
     b. Patching FBOauth module.
   Option b was eliminated to avoid patching which would make upgrading and maintenance difficult. Option a would have required additional code/module to disable the default message thrown by FBOauth module. Using a hook in this case seemed cleaner and faster.