#ifndef LIVING_LIFE_PAGE_INCLUDED
#define LIVING_LIFE_PAGE_INCLUDED




#include "minorGems/ui/event/ActionListener.h"
#include "minorGems/util/SimpleVector.h"

#include "minorGems/game/game.h"


#include "GamePage.h"


#include "pathFind.h"

#include "animationBank.h"

#include "TextField.h"




typedef struct LiveObject {
        int id;

        int displayID;
        
        double age;
        double ageRate;
        
        double lastAgeSetTime;
        
        int foodStore;
        int foodCapacity;


        int holdingID;
        
        char holdingFlip;

        char heldPosOverride;
        doublePair heldObjectPos;

        AnimType curAnim;
        AnimType lastAnim;
        double lastAnimFade;

        // anim tracking for held object
        AnimType curHeldAnim;
        AnimType lastHeldAnim;
        double lastHeldAnimFade;



        // furture states that curAnim should fade to, one at a time
        SimpleVector<AnimType> futureAnimStack;
        SimpleVector<AnimType> futureHeldAnimStack;
        
        int animationFrameCount;
        int heldAnimationFrameCount;

        int animationFrozenRotFrameCount;
        int heldAnimationFrozenRotFrameCount;

        // for special case where held animation is all-zero
        // we can freeze moving animation when player stops moving and
        // then simply resume when they start moving again
        char heldAnimationFrameFrozen;
        

        float heat;
        

        int numContained;
        int *containedIDs;
        

        // current fractional grid position and speed
        doublePair currentPos;
        // current speed is move delta per frame
        double currentSpeed;

        // for instant reaction to move command when server hasn't
        // responded yet
        // in grid spaces per sec
        double lastSpeed;

        // recompute speed periodically during move so that we don't
        // fall behind when frame rate fluctuates
        double timeOfLastSpeedUpdate;
        
        // destination grid position
        int xd;
        int yd;
        
        // last confirmed stationary position of this
        // object on the server (from the last player_update)
        int xServer;
        int yServer;
        

        int pathLength;
        GridPos *pathToDest;

                
        int closestDestIfPathFailedX;
        int closestDestIfPathFailedY;
        

        int currentPathStep;
        doublePair currentMoveDirection;
        

        // how long whole move should take
        double moveTotalTime;
        
        // wall clock time in seconds object should arrive
        double moveEtaTime;

        
        char inMotion;
        
        char displayChar;

        char pendingAction;
        float pendingActionAnimationProgress;

        
        // NULL if no active speech
        char *currentSpeech;
        double speechFade;
        // wall clock time when speech should start fading
        double speechFadeETATime;
        
    } LiveObject;





class LivingLifePage : public GamePage {
        
    public:

        LivingLifePage();
        ~LivingLifePage();
        

        virtual void draw( doublePair inViewCenter, 
                           double inViewSize );
        
        virtual void step();
  
        virtual void makeActive( char inFresh );
        

        virtual void pointerMove( float inX, float inY );
        virtual void pointerDown( float inX, float inY );
        virtual void pointerDrag( float inX, float inY );
        virtual void pointerUp( float inX, float inY );

        virtual void keyDown( unsigned char inASCII );
        
        virtual void keyUp( unsigned char inASCII );

        
    protected:
        
        char *mServerAddress;
        int mServerPort;

        int mServerSocket;

        int mFirstServerMessagesReceived;
        
        


        int mMapD;

        int *mMap;
        
        int *mMapAnimationFrameCount;
        
        // all tiles on ground work their way toward animation type of
        // "ground" but may have a lingering types after being dropped
        AnimType *mMapCurAnimType;
        AnimType *mMapLastAnimType;
        double *mMapLastAnimFade;
        
        // 0,0 for most, except for a newly-dropped object
        // as it slides back into grid position
        doublePair *mMapDropOffsets;
        

        // true if left-right flipped (to match last drop)
        // not tracked on server, so resets when object goes off of screen
        char *mMapTileFlips;
        

        SimpleVector<int> *mMapContainedStacks;

        int mMapOffsetX;
        int mMapOffsetY;


        char mEKeyDown;
        

        SpriteHandle mFoodEmptySprite;
        SpriteHandle mFoodFullSprite;
        

        int mLastMouseOverID;
        int mCurMouseOverID;
        
        double mLastMouseOverFade;


        SpriteHandle mChalkBlotSprite;
        
        
        // not visible, but used for its text filtering
        // capabilities
        TextField mSayField;
        

        void computePathToDest( LiveObject *inObject );


        LiveObject *getOurLiveObject();
        

        void clearLiveObjects();
        
        void drawChalkBackgroundString( doublePair inPos, 
                                        const char *inString,
                                        double inFade,
                                        double inMaxWidth,
                                        int inForceMinChalkBlots = -1 );

    };



#endif
