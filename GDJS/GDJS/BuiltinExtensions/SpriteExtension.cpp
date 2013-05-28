/** \file
 *  Game Develop
 *  2008-2013 Florian Rival (Florian.Rival@gmail.com)
 */

#include "GDJS/BuiltinExtensions/SpriteExtension.h"
#include "GDCore/Events/InstructionMetadata.h"
#include <wx/intl.h>
//Ensure the wxWidgets macro "_" returns a std::string
#if defined(_)
    #undef _
#endif
#define _(s) std::string(wxGetTranslation((s)).mb_str())

SpriteExtension::SpriteExtension()
{
    SetExtensionInformation("Sprite",
                          _("Sprite"),
                          _("Extension for adding animated objects in the scene, which can contain animations with directions within each."),
                          "Compil Games",
                          "Freeware");
    CloneExtension("Game Develop C++ platform", "Sprite");

    std::map<std::string, gd::InstructionMetadata > & spriteActions = GetAllActionsForObject("Sprite");
    std::map<std::string, gd::InstructionMetadata > & spriteConditions = GetAllConditionsForObject("Sprite");
    std::map<std::string, gd::ExpressionMetadata > & spriteExpressions = GetAllExpressionsForObject("Sprite");
    spriteActions["ChangeBlendMode"].codeExtraInformation.
        SetFunctionName("setBlendMode").SetIncludeFile("spriteruntimeobject.js");
    spriteActions["Opacity"].codeExtraInformation.
        SetFunctionName("setOpacity").SetAssociatedGetter("getOpacity").SetIncludeFile("spriteruntimeobject.js");
    spriteConditions["BlendMode"].codeExtraInformation.
        SetFunctionName("getBlendMode").SetIncludeFile("spriteruntimeobject.js");
    spriteConditions["Opacity"].codeExtraInformation.
        SetFunctionName("getOpacity").SetIncludeFile("spriteruntimeobject.js");

    spriteActions["ChangeAnimation"].codeExtraInformation.
        SetFunctionName("setAnimation").SetAssociatedGetter("getAnimation");
    spriteActions["ChangeDirection"].codeExtraInformation.
        SetFunctionName("setDirectionOrAngle").SetAssociatedGetter("getDirectionOrAngle");
    spriteActions["ChangeSprite"].codeExtraInformation.
        SetFunctionName("setAnimationFrame").SetAssociatedGetter("getAnimationFrame");
    spriteConditions["Animation"].codeExtraInformation.
        SetFunctionName("getAnimation");
    spriteConditions["Direction"].codeExtraInformation.
        SetFunctionName("getDirectionOrAngle");
    spriteConditions["Sprite"].codeExtraInformation.
        SetFunctionName("getAnimationFrame");

    spriteActions["ChangeScaleWidth"].codeExtraInformation.
        SetFunctionName("setScaleX").SetAssociatedGetter("getScaleX");
    spriteActions["ChangeScaleHeight"].codeExtraInformation.
        SetFunctionName("setScaleY").SetAssociatedGetter("getScaleY");
    spriteConditions["ScaleWidth"].codeExtraInformation
        .SetFunctionName("getScaleX");
    spriteConditions["ScaleHeight"].codeExtraInformation
        .SetFunctionName("getScaleY");
    spriteActions["TourneVersPos"].codeExtraInformation.
        SetFunctionName("turnTowardPosition");
    spriteActions["TourneVers"].codeExtraInformation.
        SetFunctionName("turnTowardObject");

    GetAllConditions()["Collision"].codeExtraInformation //No pixel perfect collision for now on the JS platform.
        .SetFunctionName("gdjs.objectTools.hitBoxesCollisionTest");
    GetAllConditions()["EstTourne"].codeExtraInformation
        .SetFunctionName("gdjs.objectTools.turnedTowardTest");

    spriteExpressions["X"].codeExtraInformation.
        SetFunctionName("getPointX");
    spriteExpressions["Y"].codeExtraInformation.
        SetFunctionName("getPointY");
    spriteExpressions["PointX"].codeExtraInformation.
        SetFunctionName("getPointX");
    spriteExpressions["PointY"].codeExtraInformation.
        SetFunctionName("getPointY");
    spriteExpressions["Direc"].codeExtraInformation. //Deprecated
        SetFunctionName("getDirectionOrAngle");
    spriteExpressions["Direction"].codeExtraInformation.
        SetFunctionName("getDirectionOrAngle");
    spriteExpressions["Anim"].codeExtraInformation.  //Deprecated
        SetFunctionName("getAnimation");
    spriteExpressions["Animation"].codeExtraInformation.
        SetFunctionName("getAnimation");
    spriteExpressions["Sprite"].codeExtraInformation.
        SetFunctionName("getAnimationFrame");
    spriteExpressions["ScaleX"].codeExtraInformation.
        SetFunctionName("getScaleX");
    spriteExpressions["ScaleY"].codeExtraInformation.
        SetFunctionName("getScaleY");

/*

    //Declaration of all objects available
    {

        obj.AddAction("PauseAnimation",
                       _("Pause the animation"),
                       _("Pause the current animation of the object"),
                       _("Pause the current animation of _PARAM0_"),
                       _("Animations and images"),
                       "res/actions/animation24.png",
                       "res/actions/animation.png")

            .AddParameter("object", _("Object"), "Sprite", false)
            .codeExtraInformation.SetFunctionName("StopAnimation").SetIncludeFile("GDL/SpriteObject.h");


        obj.AddAction("PlayAnimation",
                       _("Play the animation"),
                       _("Play the current animation of the object"),
                       _("Play the current animation of _PARAM0_"),
                       _("Animations and images"),
                       "res/actions/animation24.png",
                       "res/actions/animation.png")

            .AddParameter("object", _("Object"), "Sprite", false)
            .codeExtraInformation.SetFunctionName("PlayAnimation").SetIncludeFile("GDL/SpriteObject.h");


        obj.AddAction("ChangeScale",
                       _("Modify the scale of an object"),
                       _("Modify the scale of the specified object."),
                       _("Do _PARAM1__PARAM2_ to the scale of _PARAM0_"),
                       _("Size"),
                       "res/actions/scale24.png",
                       "res/actions/scale.png")

            .AddParameter("object", _("Object"), "Sprite", false)
            .AddParameter("operator", _("Modification's sign"), "",false)
            .AddParameter("expression", _("Value"), "",false)
            .codeExtraInformation.SetFunctionName("ChangeScale").SetIncludeFile("GDL/SpriteObject.h");

        obj.AddCondition("AnimStopped",
                       _("Animation is paused"),
                       _("Test if the animation of an object is paused"),
                       _("The animation of _PARAM0_ is paused"),
                       _("Animations and images"),
                       "res/conditions/animation24.png",
                       "res/conditions/animation.png")

            .AddParameter("object", _("Object"), "Sprite", false)
            .codeExtraInformation.SetFunctionName("IsAnimationStopped").SetIncludeFile("GDL/SpriteObject.h");

        obj.AddCondition("AnimationEnded",
                       _("Animation finished"),
                       _("Check if the animation being played by the Sprite object is finished."),
                       _("The animation of _PARAM0_ is finished"),
                       _("Animations and images"),
                       "res/conditions/animation24.png",
                       "res/conditions/animation.png")

            .AddParameter("object", _("Object"), "Sprite", false)
            .codeExtraInformation.SetFunctionName("AnimationEnded").SetIncludeFile("GDL/SpriteObject.h");

        obj.AddCondition("BlendMode",
                       _("Blend mode"),
                       _("Compare the number of the blend mode currently used by an object"),
                       _("The number of the current blend mode of _PARAM0_ is _PARAM1__PARAM2_"),
                       _("Effects"),
                       "res/conditions/opacity24.png",
                       "res/conditions/opacity.png")

            .AddParameter("object", _("Object"), "Sprite", false)
            .AddParameter("relationalOperator", _("Sign of the test"), "",false)
            .AddParameter("expression", _("Value to test  ( 0 : Alpha, 1 : Add, 2 : Multiply, 3 : None )"), "",false)
            .codeExtraInformation.SetFunctionName("GetBlendMode").SetManipulatedType("number").SetIncludeFile("GDL/SpriteObject.h");

        obj.AddAction("CopyImageOnImageOfSprite",
                       _("Copy an image on the current one of an object"),
                       _("Copy an image on the current image of an object.\nNote that the source image must be preferably kept loaded in memory."),
                       _("Copy image _PARAM2_ on the current of _PARAM0_ at _PARAM3_;_PARAM4_"),
                       _("Effects"),
                       "res/copy24.png",
                       "res/copyicon.png")

            .AddParameter("object", _("Object"), "Sprite", false)
            .AddCodeOnlyParameter("currentScene", "")
            .AddParameter("string", _("Name of the source image"), "",false)
            .AddParameter("expression", _("X position"), "",false)
            .AddParameter("expression", _("Y position"), "",false)
            .AddParameter("yesorno", _("Should the copy take in account the source transparency\?"), "",false)
            .codeExtraInformation.SetFunctionName("CopyImageOnImageOfCurrentSprite").SetIncludeFile("GDL/SpriteObject.h");



        obj.AddAction("CreateMaskFromColorOnActualImage", //Actual is indeed a mistake : Current should have been chosen.
                       _("Make a color of the image of an object transparent"),
                       _("Make a color of the image of an object transparent."),
                       _("Make color _PARAM1_ of the current image of _PARAM0_ transparent"),
                       _("Effects"),
                       "res/actions/opacity24.png",
                       "res/actions/opacity.png")

            .AddParameter("object", _("Object"), "Sprite", false)
            .AddParameter("color", _("Color to make transparent"), "",false)
            .codeExtraInformation.SetFunctionName("MakeColorTransparent").SetIncludeFile("GDL/SpriteObject.h");


        obj.AddAction("ChangeColor",
                       _("Change the global color"),
                       _("Change the global color of an object. The default color is white."),
                       _("Change color of _PARAM0_ to _PARAM1_"),
                       _("Effects"),
                       "res/actions/color24.png",
                       "res/actions/color.png")

            .AddParameter("object", _("Object"), "Sprite", false)
            .AddParameter("color", _("Color"), "",false)
            .codeExtraInformation.SetFunctionName("SetColor").SetIncludeFile("GDL/SpriteObject.h");


        obj.AddAction("ChangeBlendMode",
                       _("Change Blend mode"),
                       _("Change the number of the blend mode of an object.\nThe default blend mode is 0 ( Alpha )."),
                       _("Change Blend mode of _PARAM0_ to _PARAM1_"),
                       _("Effects"),
                       "res/actions/color24.png",
                       "res/actions/color.png")

            .AddParameter("object", _("Object"), "Sprite", false)
            .AddParameter("expression", _("Mode ( 0 : Alpha, 1 : Add, 2 : Multiply, 3 : None )"), "",false)
            .codeExtraInformation.SetFunctionName("SetBlendMode").SetIncludeFile("GDL/SpriteObject.h");


        obj.AddAction("FlipX",
                       _("Flip the object horizontally"),
                       _("Flip the object horizontally"),
                       _("Flip horizontally _PARAM0_ : _PARAM1_"),
                       _("Effects"),
                       "res/actions/flipX24.png",
                       "res/actions/flipX.png")

            .AddParameter("object", _("Object"), "Sprite", false)
            .AddParameter("yesorno", _("Activate flipping"), "",false)
            .codeExtraInformation.SetFunctionName("FlipX").SetIncludeFile("GDL/SpriteObject.h");


        obj.AddAction("FlipY",
                       _("Flip the object vertically"),
                       _("Flip the object vertically"),
                       _("Flip vertically _PARAM0_ : _PARAM1_"),
                       _("Effects"),
                       "res/actions/flipY24.png",
                       "res/actions/flipY.png")

            .AddParameter("object", _("Object"), "Sprite", false)
            .AddParameter("yesorno", _("Activate flipping"), "",false)
            .codeExtraInformation.SetFunctionName("FlipY").SetIncludeFile("GDL/SpriteObject.h");

        obj.AddCondition("SourisSurObjet",
                       _("The cursor is on an object"),
                       _("Test if the cursor is over a Sprite object. The test is accurate by default (check that the cursor is not on a transparent pixel)."),
                       _("The cursor is on _PARAM0_"),
                       _("Mouse"),
                       "res/conditions/surObjet24.png",
                       "res/conditions/surObjet.png")

            .AddParameter("object", _("Object"), "Sprite", false)
            .AddCodeOnlyParameter("currentScene", "")
            .AddParameter("yesorno", _("Precise test ( yes by default )"), "", true).SetDefaultValue("yes")
            .codeExtraInformation.SetFunctionName("CursorOnObject").SetIncludeFile("GDL/BuiltinExtensions/SpriteTools.h");
        #endif

    }

*/
}