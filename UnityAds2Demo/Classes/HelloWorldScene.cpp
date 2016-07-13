#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    this->initUnityAdsFunc();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);



    // Add show ad button
    auto showAdItem = MenuItemImage::create(
                                           "UnityChan_logo.png",
                                           "UnityChan_logo.png",
                                           CC_CALLBACK_1(HelloWorld::showUnityAdsFunc, this));

    showAdItem->setPosition(Vec2(origin.x + showAdItem->getContentSize().width,
                                origin.y + showAdItem->getContentSize().height));

    menu->addChild(showAdItem, 1);


    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    titleLabel = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    titleLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - titleLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(titleLabel, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::initUnityAdsFunc()
{

    const char* gameIdAndroid = "1055529";
    UnityAdsInit(gameIdAndroid, false);
}

void HelloWorld::showUnityAdsFunc(Ref* pSender)
{
    const char* zoneString = "rewardedVideo";
    if(UnityAdsIsReady(zoneString)) {
        UnityAdsShow(zoneString);
    } else {
        CCLOG("[UnityAds cpp test] yet cannot show");
    }
}

void HelloWorld::rewardPlayer(const char *placementId)
{

    CCLOG("[UnityAds cpp test] rewarded");
    const char* targetStr = "rewardedVideo";
    if(strcmp(placementId, targetStr) == 0){
        if(titleLabel){
            const char* text = "Congrats!";
            titleLabel->setString(text);
        }
    }
}
