#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TREE_POOL_MAX 1000000000
#define OPS_POOL_MAX   100000000

static const char *solved = "RRRRYYYYBBBBOOOOWWWWGGGG";

static int ops0[24] = {1,3,0,2,21,20,6,7,4,5,10,11,12,13,14,15,9,8,18,19,16,17,22,23};
static int ops1[24] = {0,1,8,10,5,7,4,6,15,9,14,11,12,13,20,22,16,17,18,19,3,21,2,23};
static int ops2[24] = {0,19,2,17,4,1,6,3,9,11,8,10,12,7,14,5,16,13,18,15,20,21,22,23};

typedef struct tree {
    char cfg[25];
    char *ops;
    struct tree *left;
    struct tree *right;
} tree_t;

typedef struct tree_pool {
    tree_t *base;
    size_t size;
    size_t max;
} tree_pool_t;

typedef struct ops_pool {
    char *base;
    size_t size;
    size_t max;
} ops_pool_t;

static void update(char *new_cfg, char *old_cfg, int op) {
    int *targets = op == 0 ? ops0 : (op == 1 ? ops1 : ops2);
    for (size_t i=0; i<24; i++)
        new_cfg[i] = old_cfg[targets[i]];
}

static void tree_print(tree_t *t) {
    if (!t)
        return;

    tree_print(t->left);
    printf("%s: '%s'\n", t->cfg, t->ops);
    tree_print(t->right);
}

static tree_t *tree_init(const char *cfg, char *ops, tree_pool_t *tree_pool) {
    if (tree_pool->size >= tree_pool->max) {
        fprintf(stderr, "tree size exceeds maximum bytes threshold");
        exit(1);
    }
    
    tree_t *t = &tree_pool->base[tree_pool->size];
    tree_pool->size++;
    memcpy(t->cfg, cfg, 24);
    t->ops = ops;

    return t;
}

static int tree_update(tree_t *t, char *cfg, char *ops, tree_pool_t *tree_pool) {
    int r = memcmp(cfg, t->cfg, 24);
    if (!r)
        return 1;

    if (r < 0)
        if (!t->left) t->left = tree_init(cfg, ops, tree_pool);
        else return tree_update(t->left, cfg, ops, tree_pool);
    else
        if (!t->right) t->right = tree_init(cfg, ops, tree_pool);
        else return tree_update(t->right, cfg, ops, tree_pool);

    return 0;
}

static void makedb(void) {
    tree_pool_t tree_pool = {0};
    tree_pool.max = TREE_POOL_MAX / sizeof(*tree_pool.base);
    tree_pool.base = calloc(tree_pool.max, sizeof(*tree_pool.base));

    ops_pool_t ops_pool = {0};
    ops_pool.max = OPS_POOL_MAX;
    ops_pool.base = calloc(ops_pool.max, 1);
    ops_pool.size = 1;

    if (!tree_pool.base || !ops_pool.base) {
        fprintf(stderr, "out of memory");
        exit(1);
    }

    char *empty_str = ops_pool.base;
    tree_t *t = tree_init(solved, empty_str, &tree_pool);

    size_t i = 0;
    size_t start_pos = 0;
    size_t added = 1;

    while (added) {
        added = 0;

        size_t old_size = tree_pool.size;
        for (size_t k=start_pos; k<old_size; k++) {
            char *cfg = tree_pool.base[k].cfg;
            char *ops = tree_pool.base[k].ops;

            for (int op=0; op<3; op++) {
                size_t new_ops_size = i + 2;
                if (ops_pool.size + new_ops_size >= ops_pool.max) {
                    fprintf(stderr, "ops size exceeds maximum bytes threshold");
                    exit(1);
                }

                char cfg_new[25] = {0};
                update(cfg_new, cfg, op);
                char *new_ops = &ops_pool.base[ops_pool.size];
                ops_pool.size += new_ops_size;

                memcpy(new_ops, ops, i);
                new_ops[i] = op + 48;

                int cfg_added = !tree_update(t, cfg_new, new_ops, &tree_pool);

                if (!cfg_added)
                    ops_pool.size -= new_ops_size;
                else
                    added++;
            }
        }

        start_pos = tree_pool.size - added;
        i++;
    }

    tree_print(t);
    free(tree_pool.base);
    free(ops_pool.base);
}

int main(int argc, char **argv) {
    makedb();
    return 0;
}

