[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/IRMe_XOA)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-7f7980b617ed060a017424585567c406b6ee15c891e84e1186181d67ecf80aa0.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=12914228)
# Week7_2

以下にREADMEの例が書いてあります。自由に編集してください。READMEをちゃんと書かないと減点します。READMEの書き方（マークダウンの文法）は[こちら](https://eeic-software1.github.io/2023/markdown/)。

# スイカ in C

物理エンジンを適用した、ターミナルベースのスイカゲームを作りました。

```
SCORE : 14650
|                                    |
|                2222                |
|               222222               |
|                 22                 |
|                                    |
|                                    |
|                                    |
|                                    |
|                                    |
|XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
|                                    |
|                                    |
|                                    |
|                                    |
|                                    |
| 11                                 |
|1111                                |
| 1333                               |
|3333333                             |
|3333333          77777        444   |
| 33333   1111177777777777   44444444|
|  666666661117777777777777 444444444|
|666666666666777777777777777 44444444|
|66666666666677777777777777   44444  |
|666666666666 7777777777777333333    |
| 66666666666   777777777 33333331111|
|  66666666                33333 1111|
|------------------------------------|
> 
```

<details>
<summary>Google Cloud Shell Editor で実行したときのスクリーンショット</summary>

![Screenshot of the game](/images/ScreenshotGame.png)

</details>

## メンバー
JEONG Seung Min

## 実行方法

以下のコマンドでコンパイルできます。
```console
$ gcc -o suica *.c -lm
```

その後、以下のコマンドで実行します。
```console
$ ./suica
```

コマンドライン引数で画面表示に関する設定ができます。画面の最大高さ（文字）、最大幅（文字）、フォントのアスペクト比（高さ / 幅）の一部または全部を変更できます。
```console
suica [height] [width] [aspect]
```

例えば、次のように最大高さを40文字、 最大幅を60文字に変更できます。
```console
$ ./suica 40 60
```

## 操作方法

実行したあとの画面は次のようになります。

```
SCORE : 0
|               444444               |
|              44444444              |
|             444444444              |
|              44444444              |
|                                    |
|                                    |
|                                    |
|                                    |
|                                    |
|XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
|                                    |
|                                    |
|                                    |
|                                    |
|                                    |
|                                    |
|                                    |
|                                    |
|                                    |
|                                    |
|                                    |
|                                    |
|                                    |
|                                    |
|                                    |
|                                    |
|                                    |
|------------------------------------|
> 
```

<details>
<summary>Google Cloud Shell Editor で実行したときのスクリーンショット</summary>

![Screenshot of initial screen](/images/ScreenshotInit.png)

</details>

最後の`>`は入力を待っている状態を表しています。この状態の時のみキーを押してください。

`A`と`D`で落とす位置を左右に移動できます。

`S`で果物を落とします。

`.`でゲームを終了します。

ゲームオーバーしたあと`R`を押すと、リスタートできます。

## ルール

同じ数字の果物が接触すると合体し、一つ大きい数字を持つ果物になります。

果物を落とした後、安定な状態になると再び入力ができるようになります。

この時、`XXXXX`で表示された線の上に中心がある果物が一つでもある場合、ゲームオーバーになります。

## 推しポイント

- 果物を落とし、シミュレーションを実行する関数です。
- 安定な状態になる、または設定された最大時間が経過すると終わります。

```c
//Defined in world.c

void run(World *world) {
    addFruit(&(world->f), world->dr.f);
    world->dr.f = NULL;
    updatePrev(world);
    for(int frame = 0; frame < _maxf; frame++) {
        for(int sf = 0; sf < _subframe; sf++) {
            applyGravity(world->f);
            checkBoundCol(world->f);
            checkFruitCol(world->f, &(world->col));
            applyVelocity(world->f);
            merge(world);
        }
        display(world, 1);
        if(world->merged) {
            world->merged = 0;
            frame = 0;
            updatePrev(world);
        };
        if(!(frame % _checkf) && frame > 0) {
            updatePrev(world);
            if(world->stopped) break;
        }
        thrd_sleep(&(world->delay), NULL);
    }
    checkGameOver(world);
    if(!world->gameOver) resetDropper(&(world->dr));
}
```

- 果物のリスト、衝突ペアのリストを引数とする関数です。
- 衝突が起きた場合、それぞれの果物に力積（速度変化）を与えます。
- 衝突ペアに追加された果物は後に合体します。

```c
//Defined in physics.c

void checkFruitCol(Fruit *f, ColPair **col) {
    Fruit *f1 = f, *f2;
    double pd;
    while(f1 != NULL) {
        f2 = f1->prev;
        while(f2 != NULL) {
            pd = f1->r + f2->r - vecDist(f1->x, f2->x);
            if(pd > 0.) {
                Vector n = vecNormalize(vecSub(f1->x, f2->x));
                Vector t = vecCross(n, 1.);
                Vector v = vecSub(f1->v, f2->v);
                double mr = 1 / (1 / f1->m + 1 / f2->m);
                double vb = getBiasVel(pd);
                double jn = getNormalImpulse(n, v, mr, vb);
                double jt = getTangentImpulse(t, v, mr, jn);
                vecMultAddA(&(f1->v), n, jn / f1->m);
                vecMultAddA(&(f1->v), t, jt / f1->m);
                vecMultAddA(&(f2->v), n, -jn / f2->m);
                vecMultAddA(&(f2->v), t, -jt / f2->m);
                if(f1->type == f2->type) addColPair(col, f1, f2);
            }
            f2 = f2->prev;
        }
        f1 = f1->prev;
    }
}
```

- 衝突の法線ベクトル、相対速度、換算質量、バイアス速度で力積を計算する関数です。
- バイアス速度がないと果物が他の果物の中に入ることがあります。

```c
//Defined in physics.c

double getNormalImpulse(Vector n, Vector v, double mr, double vb) {
    double vn = vecDot(n, v) - vb;
    if(vn > 0.) return 0.;
    return -(1 + _e) * mr * vn;
}

double getTangentImpulse(Vector t, Vector v, double mr, double jn) {
    double vt = vecDot(t, v);
    if(vt > 0.) {
        if(_mu * jn > mr * vt) return -mr * vt;
        return -_mu * jn;
    }
    if(_mu * jn > mr * -vt) return -mr * vt;
    return _mu * jn;
}
```

- 衝突ペアに基づいて果物を合体させる関数です。
- 衝突して消える予定の果物が関わった他の衝突ペアは非活性化されます。

```c
//Defined in world.c

void merge(World *world) {
    world->merged = 0;
    ColPair *colp;
    while(world->col != NULL) {
        if(world->col->active) {
            Fruit *f1 = world->col->f1;
            Fruit *f2 = world->col->f2;
            int type = f1->type;
            ColPair *colp = world->col->prev;
            while(colp != NULL) {
                if(colp->f1 == f1 || colp->f2 == f1 ||
                   colp->f1 == f2 || colp->f2 == f2) {
                    colp->active = 0;
                }
                colp = colp->prev;
            }
            if(type < _ftn - 1) {
                Vector x = vecMult(vecAdd(f1->x, f2->x), .5);
                Vector v = vecMult(vecAdd(f1->v, f2->v), .5);
                Fruit *newf = createFruit(x, v, type + 1);
                addFruit(&(world->f), newf);
            }
            deleteFruit(&(world->f), world->col->f1);
            deleteFruit(&(world->f), world->col->f2);
            world->score += _fs[type];
            world->merged = 1;
        }
        colp = world->col->prev;
        free(world->col);
        world->col = colp;
    }
}
```

## 変数

`consts.c`で定義された変数を紹介します。

- 乱数関連
  - `_seed` 乱数のシード

- 画面表示に関する既定値
  - `_twidth` 画面の幅（文字）の既定値
  - `_theight` 画面の高さ（文字）の既定値
  - `_aspect` フォントのアスペクト比の既定値

- ボードのサイズ
  - `_boundx` 右の境界のx座標
  - `_boundy` 下の境界のy座標

- 物理計算に関する変数
  - `_gravity` 重力
  - `_e` 弾性係数
  - `_mu` 摩擦係数
  - `_bias` バイアス速度の係数
  - `_pdm` 最小限の侵入深さ

- フレームと時間関連
  - `_fps` フレームレート
  - `_subframe` フレームの間の計算回数
  - `_dt` 時間間隔

- 安定化関連
  - `_maxt` シミュレーションの最大時間（秒）
  - `_checkt` 安定な状態なのかチェックする時間間隔（秒）
  - `_maxf` シミュレーションの最大時間（フレーム）
  - `_checkf` 安定な状態なのかチェックする時間間隔（フレーム）
  - `_xth` 安定な状態になる移動のしきい値
  - `_vth` 安定な状態になる速度のしきい値

- 果物の性質
  - `_ftn` 果物の種類
  - `_dftn` 落とす果物の種類
  - `_fr` 果物の半径
  - `_fs` 果物が合体した時の点数
  - `_fch` 果物を表す文字
  - `_fcol` 果物の色（エスケープシーケンス）

- 落とされる果物関連
  - `_drstep` 落とす位置の移動の細かさ
  - `_drxn` 落とす位置のランダムの度合い
  - `_drvn` 初期速度のランダムの度合い

## 参考文献

- [box2d-lite](https://github.com/erincatto/box2d-lite)
- [Impulse-based Dynamic Simulation](https://graphics.stanford.edu/courses/cs468-03-winter/Papers/ibds.pdf)
