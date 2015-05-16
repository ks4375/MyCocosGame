#include "OptionScene.h"
#include "GameMainScene.h"
#include "TitleScene.h"

USING_NS_CC;

Scene* GameMain::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameMain::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameMain::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameMain::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Game Main", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "GameMain" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    // イベントリスナー作成
    auto listener = EventListenerTouchOneByOne::create(); // シングルタッチ
    // イベントを飲み込むかどうか
    listener->setSwallowTouches(true);
    // タッチ開始
    listener->onTouchBegan = [](Touch* touch, Event* event){
        // タッチ開始時の処理を書く
        //auto aaa = touch->getLocation();
        //CCLOG("x=%f, y=%f", aaa.x, aaa.y);
        Director::getInstance()->replaceScene(Option::createScene());
		return true;
    };
    // タッチ中
    listener->onTouchMoved = [](Touch* touch, Event* event){
        // タッチ中の処理を書く
    };
    // タッチ終了
    listener->onTouchEnded = [](Touch* touch, Event* event){
        // タッチ終了時の処理を書く
    };
    // タッチキャンセル
    listener->onTouchCancelled = [](Touch* touch, Event* event){
        // タッチキャンセル時の処理を書く
    };
    // イベントリスナーを登録
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,
                                                                       this);
    
    return true;
}


void GameMain::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
