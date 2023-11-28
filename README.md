[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/IRMe_XOA)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-7f7980b617ed060a017424585567c406b6ee15c891e84e1186181d67ecf80aa0.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=12914228)
# Week7_2

以下にREADMEの例が書いてあります。自由に編集してください。READMEをちゃんと書かないと減点します。READMEの書き方（マークダウンの文法）は[こちら](https://eeic-software1.github.io/2023/markdown/)。

# SUICA

物理エンジンを適用した、ターミナルベースのスイカゲームを作りました。

```
SCORE : 15300
|                                     |
|                22222                |
|                22222                |
|                                     |
|                                     |
|                                     |
|                                     |
|XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
|                                     |
|                                     |
|                                     |
|                                     |
|1111                                 |
|11114   22222                        |
|44444444222225555            44444444|
|444444444 5555555555        444444444|
| 4444444  55555555555  7777774444444 |
|  666666665555555555777777777777     |
|666666666666 5555  77777777777777    |
|666666666666633333 77777777777777    |
|6666666666663333333777777777777722222|
|  66666666   333333  777777777  22222|
|-------------------------------------|
> 
```

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
|                                     |
|                22222                |
|                22222                |
|                                     |
|                                     |
|                                     |
|                                     |
|XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
|                                     |
|                                     |
|                                     |
|                                     |
|                                     |
|                                     |
|                                     |
|                                     |
|                                     |
|                                     |
|                                     |
|                                     |
|                                     |
|                                     |
|-------------------------------------|
> 
```

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
            applyImpulse(world->f);
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
                Vector v = vecSub(f1->v, f2->v);
                double rm = 1 / (1 / f1->m + 1 / f2->m);
                double vb = getBiasVel(pd);
                Vector j = getImpulse(n, v, rm, vb);
                vecAddA(&(f1->j), j);
                vecAddA(&(f2->j), vecMinus(j));
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

Vector getImpulse(Vector n, Vector v, double rm, double vb) {
    double vn_ = vecDot(n, v) - vb;
    if(vn_ > 0.) return (Vector){0., 0.};
    Vector vn = vecMult(n, vn_);
    Vector vt = vecSub(v, vn);
    Vector t = vecNormalize(vt);
    double vt_ = vecNorm(vt);
    double j = -(1 + _e) * rm * vn_;
    Vector jn = vecMult(n, j);
    Vector jt;
    if(j * _mu > rm * vt_) {
        jt = vecMult(t, -rm * vt_);
    }
    else {
        jt = vecMult(t, -j * _mu);
    }
    return vecAdd(jn, jt);
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
                Fruit *newf = createFruit(x.x, x.y, type + 1);
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

`consts.c`で定義された変数を紹介します。自由に変更してみてください。

`_seed` 乱数のシード

`_twidth` 画面の幅（文字）の既定値

`_theight` 画面の高さ（文字）の既定値

`_aspect` フォントのアスペクト比の既定値

`_boundn` 境界の法線ベクトル

`_boundx` 右の境界のx座標

`_boundy` 下の境界のy座標

`_gravity` 重力

`_e` 弾性係数

`_mu` 摩擦係数

`_bias` バイアス速度の係数

`_pdm` 最小限の侵入深さ

`_fps` フレームレート

`_subframe` フレームの間の計算回数

`_dt` 時間間隔

`_maxt` シミュレーションの最大時間（秒）

`_checkt` 安定な状態なのかチェックする時間間隔（秒）

`_maxf` シミュレーションの最大時間（フレーム）

`_checkf` 安定な状態なのかチェックする時間間隔（フレーム）

`_xth` 安定な状態になる移動のしきい値

`_vth` 安定な状態になる速度のしきい値

`_ftn` 果物の種類

`_dftn` 落とす果物の種類

`_fr` 果物の半径

`_fc` 果物を表す文字

`_fs` 果物が合体した時の点数

`_limity` ゲームオーバーになる境界線

`_drstep` 果物を落とす位置の移動の細かさ

`_drnr` 果物を落とす位置のランダムの度合い

## 参考文献

- [box2d-lite](https://github.com/erincatto/box2d-lite)
- [Impulse-based Dynamic Simulation](https://graphics.stanford.edu/courses/cs468-03-winter/Papers/ibds.pdf)
