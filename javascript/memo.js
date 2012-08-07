//Javascirptメモ

//Webブラウザごとのエンジン(Javascript, Rendering)
// IE : JScript, Trident
// FF : SpiderMonkey, Gecko
// Ch : V8, WebKit
// Sa : JavaScriptCore, WebKit
// Op : Charakan, Presto

//console
(function(){
    //メッセージ・オブジェクト出力
    console.log('hello');
    console.log('%s : %d', 'number', 12);
    console.debug('hello');
    console.error('hello');
    console.warn('hello');
    console.info('hello');

    //オブジェクトを見やすくダンプ
    console.dir(obj);
    console.dirxml(obj);

    //スタックトレース
    console.trace();

    //時間計測
    console.time('tm');
    alert('tm start');
    console.timeEnd('tm');
    alert('tm start');

    //呼び出し回数カウント
    console.count('cnt');

    //条件がfalseの時アサーション
    console.assert(obj != null, 'obj is null/undefined');
})();

//位置調整
(function(){
    //position属性
    // static : HTMLに従って要素を配置(default, top/leftの指定ができない)
    // fixed : ブラウザウィンドウの相対位置(スクロールに依存しない)
    // absolute : その要素からの相対位置(基本はbody,入れ子ならばその要素)
    // relative : HTMLに従って要素が配置された後、その位置を基準にした相対位置

    //座標
    // スクリーン座標 : screenX,screenY : ディスプレイの左上を原点
    // ウィンドウ座標 : clientX,clientY : ブラウザの表示領域の左上を原点(スクロールに依存しない)
    // ドキュメント座標 : pageX,pageY : ドキュメントの左上を原点(Webブラウザの独自実装)

    //相対座標
    function onclick(e){
	var x = e.clientX; //ウィンドウ座標のx座標
	var y = e.clientY; //ウィンドウ座標のy座標
	var r = e.target.getBoundingClientRect(); //クリックした要素の領域情報
	var cx = x - r.left; //クリック領域内でのx座標
	var cy = y - r.top; //クリック領域内でのy座標
    }
})();