// SPDX-License-Identifier: GPL-2.0-or-later OR MIT

#include "qca_ppe.h"

struct psch_tdm_entry {
	u8 bmp;
	u8 en_port;
	u8 de_port;
};

struct bm_tdm_entry {
	u8 port;
	u8 dir;
};

/* CPPE (IPQ60xx) port scheduler TDM -- 50 entries */
static const struct psch_tdm_entry cppe_psch_tdm[] = {
	{ 0xb7, 0, 6 }, { 0xbe, 3, 0 }, { 0xde, 6, 5 }, { 0xdd, 0, 1 },
	{ 0xbd, 5, 6 }, { 0xbe, 1, 0 }, { 0xee, 6, 4 }, { 0xcf, 0, 5 },
	{ 0x9f, 4, 6 }, { 0xbe, 5, 0 }, { 0x7e, 6, 7 }, { 0x5f, 0, 5 },
	{ 0x9f, 7, 6 }, { 0xbe, 5, 0 }, { 0xfa, 6, 2 }, { 0xbb, 0, 6 },
	{ 0x9f, 2, 5 }, { 0xcf, 6, 4 }, { 0xee, 5, 0 }, { 0xbe, 4, 6 },
	{ 0x3f, 0, 7 }, { 0x5f, 6, 5 }, { 0xde, 7, 0 }, { 0xbe, 5, 6 },
	{ 0xb7, 0, 3 }, { 0xe7, 6, 4 }, { 0xee, 3, 0 }, { 0xbe, 4, 6 },
	{ 0x9f, 0, 5 }, { 0xdd, 6, 1 }, { 0xfc, 5, 0 }, { 0xbe, 1, 6 },
	{ 0x9f, 0, 5 }, { 0x5f, 6, 7 }, { 0x7e, 5, 0 }, { 0xbe, 7, 6 },
	{ 0xaf, 0, 4 }, { 0xcf, 6, 5 }, { 0x9f, 4, 6 }, { 0xbe, 5, 0 },
	{ 0xfa, 6, 2 }, { 0xdb, 0, 5 }, { 0x9f, 2, 6 }, { 0xbe, 5, 0 },
	{ 0x7e, 6, 7 }, { 0x6f, 0, 4 }, { 0xaf, 7, 6 }, { 0x9f, 4, 5 },
	{ 0xde, 6, 0 }, { 0xf6, 5, 3 },
};

/* HPPE (IPQ807x) port scheduler TDM -- 50 entries
 * Source: ssdk_hppe.c port_scheduler0_tbl[] */
static const struct psch_tdm_entry hppe_psch_tdm[] = {
	{ 0xee, 6, 0 }, { 0xde, 4, 5 }, { 0x9f, 0, 6 }, { 0xbe, 5, 0 },
	{ 0x7e, 6, 7 }, { 0x5f, 0, 5 }, { 0x9f, 7, 6 }, { 0xbe, 5, 0 },
	{ 0xfc, 6, 1 }, { 0xdd, 0, 5 }, { 0xde, 1, 0 }, { 0xbe, 5, 6 },
	{ 0xbb, 0, 2 }, { 0xdb, 6, 5 }, { 0xde, 2, 0 }, { 0xbe, 5, 6 },
	{ 0x3f, 0, 7 }, { 0x7e, 6, 0 }, { 0xde, 7, 5 }, { 0x9f, 0, 6 },
	{ 0xb7, 5, 3 }, { 0xf6, 6, 0 }, { 0xde, 3, 5 }, { 0x9f, 0, 6 },
	{ 0xbe, 5, 0 }, { 0xee, 6, 4 }, { 0xcf, 0, 5 }, { 0x9f, 4, 6 },
	{ 0xbe, 5, 0 }, { 0x7e, 6, 7 }, { 0x5f, 0, 5 }, { 0xde, 7, 0 },
	{ 0xbe, 5, 6 }, { 0xbd, 0, 1 }, { 0xdd, 6, 5 }, { 0xde, 1, 0 },
	{ 0xbe, 5, 6 }, { 0xbb, 0, 2 }, { 0xfa, 6, 0 }, { 0xde, 2, 5 },
	{ 0x9f, 0, 6 }, { 0x3f, 5, 7 }, { 0x7e, 6, 0 }, { 0xde, 7, 5 },
	{ 0x9f, 0, 6 }, { 0xb7, 5, 3 }, { 0xf6, 6, 0 }, { 0xde, 3, 5 },
	{ 0x9f, 0, 6 }, { 0xaf, 5, 4 },
};

/* CPPE buffer manager TDM -- 98 entries */
static const struct bm_tdm_entry cppe_bm_tdm[] = {
	{ 0, 0 }, { 0, 1 }, { 5, 0 }, { 4, 1 }, { 1, 0 }, { 5, 1 },
	{ 6, 0 }, { 6, 1 }, { 0, 0 }, { 0, 1 }, { 7, 0 }, { 7, 1 },
	{ 4, 0 }, { 0, 1 }, { 6, 0 }, { 5, 1 }, { 0, 0 }, { 0, 1 },
	{ 2, 0 }, { 6, 1 }, { 7, 0 }, { 7, 1 }, { 5, 0 }, { 5, 1 },
	{ 0, 0 }, { 0, 1 }, { 6, 0 }, { 6, 1 }, { 7, 0 }, { 3, 1 },
	{ 5, 0 }, { 7, 1 }, { 0, 0 }, { 0, 1 }, { 6, 0 }, { 5, 1 },
	{ 0, 0 }, { 6, 1 }, { 7, 0 }, { 7, 1 }, { 0, 0 }, { 0, 1 },
	{ 5, 0 }, { 4, 1 }, { 6, 0 }, { 6, 1 }, { 7, 0 }, { 7, 1 },
	{ 0, 0 }, { 0, 1 }, { 4, 0 }, { 5, 1 }, { 5, 0 }, { 1, 1 },
	{ 6, 0 }, { 6, 1 }, { 0, 0 }, { 0, 1 }, { 7, 0 }, { 7, 1 },
	{ 0, 0 }, { 4, 1 }, { 5, 0 }, { 6, 1 }, { 0, 0 }, { 0, 1 },
	{ 6, 0 }, { 2, 1 }, { 7, 0 }, { 7, 1 }, { 5, 0 }, { 5, 1 },
	{ 0, 0 }, { 0, 1 }, { 6, 0 }, { 6, 1 }, { 3, 0 }, { 7, 1 },
	{ 7, 0 }, { 5, 1 }, { 0, 0 }, { 0, 1 }, { 5, 0 }, { 6, 1 },
	{ 6, 0 }, { 0, 1 }, { 7, 0 }, { 7, 1 }, { 0, 0 }, { 0, 1 },
	{ 4, 0 }, { 5, 1 }, { 6, 0 }, { 6, 1 }, { 7, 0 }, { 7, 1 },
	{ 0, 0 }, { 0, 1 },
};

/* HPPE buffer manager TDM -- 96 entries
 * Source: ssdk_hppe.c port_tdm0_tbl[] */
static const struct bm_tdm_entry hppe_bm_tdm[] = {
	{ 0, 0 }, { 5, 1 }, { 5, 0 }, { 7, 1 }, { 1, 0 }, { 6, 1 },
	{ 6, 0 }, { 0, 1 }, { 0, 0 }, { 7, 1 }, { 7, 0 }, { 5, 1 },
	{ 5, 0 }, { 0, 1 }, { 6, 0 }, { 6, 1 }, { 0, 0 }, { 3, 1 },
	{ 2, 0 }, { 7, 1 }, { 7, 0 }, { 5, 1 }, { 5, 0 }, { 0, 1 },
	{ 0, 0 }, { 6, 1 }, { 6, 0 }, { 0, 1 }, { 7, 0 }, { 7, 1 },
	{ 5, 0 }, { 5, 1 }, { 0, 0 }, { 0, 1 }, { 6, 0 }, { 6, 1 },
	{ 0, 0 }, { 0, 1 }, { 7, 0 }, { 7, 1 }, { 0, 0 }, { 5, 1 },
	{ 5, 0 }, { 4, 1 }, { 6, 0 }, { 6, 1 }, { 7, 0 }, { 0, 1 },
	{ 0, 0 }, { 7, 1 }, { 4, 0 }, { 5, 1 }, { 5, 0 }, { 0, 1 },
	{ 6, 0 }, { 6, 1 }, { 0, 0 }, { 1, 1 }, { 7, 0 }, { 7, 1 },
	{ 0, 0 }, { 5, 1 }, { 5, 0 }, { 0, 1 }, { 0, 0 }, { 6, 1 },
	{ 6, 0 }, { 0, 1 }, { 7, 0 }, { 7, 1 }, { 5, 0 }, { 5, 1 },
	{ 0, 0 }, { 0, 1 }, { 6, 0 }, { 6, 1 }, { 3, 0 }, { 0, 1 },
	{ 7, 0 }, { 7, 1 }, { 0, 0 }, { 5, 1 }, { 5, 0 }, { 0, 1 },
	{ 6, 0 }, { 6, 1 }, { 7, 0 }, { 2, 1 }, { 0, 0 }, { 7, 1 },
	{ 5, 0 }, { 5, 1 }, { 6, 0 }, { 0, 1 }, { 7, 0 }, { 6, 1 },
};

static void ppe_tdm_init(struct qca_ppe *ppe)
{
	const struct psch_tdm_entry *psch;
	const struct bm_tdm_entry *bm;
	int psch_num, bm_num;
	int i;

	if (ppe->data->type == PPE_TYPE_IPQ8074) {
		psch = hppe_psch_tdm;
		psch_num = ARRAY_SIZE(hppe_psch_tdm);
		bm = hppe_bm_tdm;
		bm_num = ARRAY_SIZE(hppe_bm_tdm);
	} else {
		psch = cppe_psch_tdm;
		psch_num = ARRAY_SIZE(cppe_psch_tdm);
		bm = cppe_bm_tdm;
		bm_num = ARRAY_SIZE(cppe_bm_tdm);
	}

	for (i = 0; i < psch_num; i++)
		ppe_w32(ppe, PPE_TM_PSCH_TDM(i),
			FIELD_PREP(PPE_PSCH_ENS_PORT_BMP, psch[i].bmp) |
			FIELD_PREP(PPE_PSCH_ENS_PORT, psch[i].en_port) |
			FIELD_PREP(PPE_PSCH_DES_PORT, psch[i].de_port));

	ppe_w32(ppe, PPE_TM_TDM_DEPTH,
		FIELD_PREP(PPE_TM_TDM_DEPTH_MASK, psch_num));

	for (i = 0; i < bm_num; i++)
		ppe_w32(ppe, PPE_PRX_TDM_CFG(i),
			FIELD_PREP(PPE_TDM_PORT_NUM, bm[i].port) |
			FIELD_PREP(PPE_TDM_DIR, bm[i].dir) |
			PPE_TDM_VALID);

	ppe_w32(ppe, PPE_PRX_TDM_CTRL,
		FIELD_PREP(PPE_TDM_DEPTH, bm_num) |
		PPE_TDM_EN);
}

static void ppe_bm_init(struct qca_ppe *ppe)
{
	const struct ppe_data *d = ppe->data;
	int i;

	for (i = 0; i < PPE_BM_PORTS; i++) {
		bool fc_en = (i < PPE_BM_PHY_START || i > d->bm_phy_end);

		ppe_w32(ppe, PPE_BM_FC_MODE(i),
			fc_en ? PPE_BM_FC_EN : 0);
		ppe_w32(ppe, PPE_BM_GROUP_ID(i), 0);
	}

	ppe_w32(ppe, PPE_BM_SHARED_GRP(0),
		FIELD_PREP(PPE_BM_SHARED_LIMIT, d->bm_group_buf));

	for (i = 0; i < PPE_BM_PORTS; i++) {
		u16 react;
		u32 w0, w1;

		if (i < PPE_BM_PHY_START)
			react = 100;
		else if (i >= d->bm_internal_start)
			react = 40;
		else
			react = 128;

		w0 = FIELD_PREP(PPE_BM_REACT_LIMIT, react) |
		     FIELD_PREP(PPE_BM_RESUME_OFF, 36) |
		     FIELD_PREP(PPE_BM_CEILING_LO, d->bm_ceiling & 0x7);
		w1 = FIELD_PREP(PPE_BM_CEILING_HI, d->bm_ceiling >> 3) |
		     FIELD_PREP(PPE_BM_WEIGHT, 4) |
		     PPE_BM_DYNAMIC;

		ppe_w32(ppe, PPE_BM_PORT_FC_W0(i), w0);
		ppe_w32(ppe, PPE_BM_PORT_FC_W1(i), w1);
	}
}

static void ppe_qm_map_set(struct qca_ppe *ppe, u32 index,
			    u8 queue_base, u8 profile)
{
	ppe_w32(ppe, PPE_QM_UCAST_MAP(index),
		FIELD_PREP(PPE_QM_PROFILE_ID, profile) |
		FIELD_PREP(PPE_QM_QUEUE_ID, queue_base));
}

static const u8 port_queue_base[PPE_NUM_PORTS] = {
	0, 144, 160, 176, 192, 208, 224, 240,
};

static const u8 port_l0_cdrr_num[PPE_NUM_PORTS] = {
	48, 16, 16, 16, 16, 16, 16, 16,
};

static void ppe_qm_init(struct qca_ppe *ppe)
{
	const struct ppe_data *d = ppe->data;
	int i, pri;

	ppe_qm_map_set(ppe, QM_SERVICE_CODE_OFFSET + 2, 8, 0);
	ppe_qm_map_set(ppe, QM_SERVICE_CODE_OFFSET + 3, 128, 8);
	ppe_qm_map_set(ppe, QM_SERVICE_CODE_OFFSET + 4, 128, 8);
	ppe_qm_map_set(ppe, QM_SERVICE_CODE_OFFSET + 5, 0, 0);
	ppe_qm_map_set(ppe, QM_SERVICE_CODE_OFFSET + 6, 8, 0);
	ppe_qm_map_set(ppe, QM_SERVICE_CODE_OFFSET + 7, 240, 0);

	for (i = 0; i < PPE_NUM_PORTS; i++)
		ppe_qm_map_set(ppe, QM_VP_PORT_OFFSET + i,
				port_queue_base[i], i);

	for (i = 0; i < PPE_NUM_PORTS; i++) {
		u8 max_pri = port_l0_cdrr_num[i];
		u8 profile;

		if (max_pri > 16)
			max_pri = 1;

		for (pri = 0; pri < 16; pri++) {
			u8 cls = (pri >= max_pri) ? max_pri - 1 : pri;

			if (i == 0) {
				profile = 0;
				ppe_w32(ppe, PPE_QM_UCAST_PRI_MAP(profile * 16 + pri),
					FIELD_PREP(PPE_QM_PRI_CLASS, cls));
				profile = 15;
				ppe_w32(ppe, PPE_QM_UCAST_PRI_MAP(profile * 16 + pri),
					FIELD_PREP(PPE_QM_PRI_CLASS, cls));
			} else {
				ppe_w32(ppe, PPE_QM_UCAST_PRI_MAP(i * 16 + pri),
					FIELD_PREP(PPE_QM_PRI_CLASS, cls));
			}
		}
	}

	for (i = 0; i < 256; i++) {
		ppe_w32(ppe, PPE_QM_UCAST_HASH_MAP(15 * 256 + i), 0);
		ppe_w32(ppe, PPE_QM_UCAST_HASH_MAP(14 * 256 + i), 0);
	}

	ppe_qm_map_set(ppe, QM_CPU_CODE_OFFSET + 101,
			port_queue_base[0] + 0, 0);

	for (i = 0; i < PPE_MAX_SERVICE_CODES; i++) {
		u32 idx = QM_SERVICE_CODE_OFFSET + (1 << 8) + i;

		if (i == 2 || i == 6)
			ppe_qm_map_set(ppe, idx, 8, 0);
		else if (i == 3 || i == 4)
			ppe_qm_map_set(ppe, idx, 128, 8);
		else
			ppe_qm_map_set(ppe, idx, 4, 0);
	}

	for (i = 0; i < PPE_MAX_CPU_CODES; i++)
		ppe_qm_map_set(ppe, QM_CPU_CODE_OFFSET + (1 << 8) + i, 4, 0);

	for (i = 0; i < PPE_NUM_PORTS; i++)
		ppe_qm_map_set(ppe, QM_VP_PORT_OFFSET + (1 << 8) + i,
				port_queue_base[i], i);

	for (i = PPE_NUM_PORTS; i < PPE_MAX_VPORT; i++)
		ppe_qm_map_set(ppe, QM_VP_PORT_OFFSET + (1 << 8) + i, 4, 0);

	for (i = 0; i < PPE_L0_UCAST_QUEUES; i++) {
		ppe_w32(ppe, PPE_QM_AC_UNI_W0(i),
			PPE_AC_EN |
			PPE_AC_SHARED_DYNAMIC |
			FIELD_PREP(PPE_AC_SHARED_WEIGHT, 4) |
			FIELD_PREP(PPE_AC_SHARED_CEILING, d->qm_ceiling));
		ppe_w32(ppe, PPE_QM_AC_UNI_W1(i), 0);
		ppe_w32(ppe, PPE_QM_AC_UNI_W2(i), 0);
		ppe_w32(ppe, PPE_QM_AC_UNI_W3(i),
			FIELD_PREP(PPE_AC_GRN_RESUME_OFF, 36));
	}

	for (i = 0; i < PPE_L0_QUEUES - PPE_L0_UCAST_QUEUES; i++) {
		ppe_w32(ppe, PPE_QM_AC_MUL_W0(i),
			PPE_AC_MUL_EN |
			FIELD_PREP(PPE_AC_MUL_CEILING, d->qm_ceiling) |
			FIELD_PREP(PPE_AC_MUL_GRN_MAX_LO, d->qm_green_max & 0x1f));
		ppe_w32(ppe, PPE_QM_AC_MUL_W1(i),
			FIELD_PREP(PPE_AC_MUL_GRN_MAX_HI, d->qm_green_max >> 5));
		ppe_w32(ppe, PPE_QM_AC_MUL_W2(i),
			FIELD_PREP(PPE_AC_MUL_GRN_RESUME_HI, 36));
	}

	ppe_w32(ppe, PPE_QM_AC_GRP_W0(0), 0);
	ppe_w32(ppe, PPE_QM_AC_GRP_W1(0),
		FIELD_PREP(PPE_AC_GRP_LIMIT, d->qm_total_buf));
	ppe_w32(ppe, PPE_QM_AC_GRP_W2(0), 0);

	ppe_m32(ppe, PPE_EG_BRIDGE_CONFIG, PPE_EG_QUEUE_CNT_EN,
		PPE_EG_QUEUE_CNT_EN);
}

struct l1_cfg {
	u8 index;
	u8 port;
	u8 pri;
	u8 drr;
};

static const struct l1_cfg l1_cfg[] = {
	{  0, 0, 0,  0 },
	{  1, 0, 0,  0 },
	{ 36, 1, 0,  8 },
	{ 37, 1, 1,  9 },
	{ 40, 2, 0, 12 },
	{ 41, 2, 1, 13 },
	{ 44, 3, 0, 16 },
	{ 45, 3, 1, 17 },
	{ 48, 4, 0, 20 },
	{ 49, 4, 1, 21 },
	{ 52, 5, 0, 24 },
	{ 53, 5, 1, 25 },
	{ 56, 6, 0, 28 },
	{ 57, 6, 1, 29 },
	{ 60, 7, 0, 32 },
	{ 61, 7, 1, 33 },
};

static void ppe_l1_scheduler_init(struct qca_ppe *ppe)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(l1_cfg); i++) {
		const struct l1_cfg *c = &l1_cfg[i];
		u32 sp_idx;

		ppe_w32(ppe, PPE_TM_L1_FLOW_MAP(c->index),
			FIELD_PREP(PPE_L1_SP_ID, c->port) |
			FIELD_PREP(PPE_L1_C_PRI, c->pri) |
			FIELD_PREP(PPE_L1_E_PRI, c->pri) |
			FIELD_PREP(PPE_L1_C_DRR_WT, 1) |
			FIELD_PREP(PPE_L1_E_DRR_WT, 1));

		sp_idx = c->port * 8 + c->pri;
		ppe_w32(ppe, PPE_TM_L1_C_SP(sp_idx),
			FIELD_PREP(PPE_L1_SP_DRR_ID, c->drr));

		ppe_w32(ppe, PPE_TM_L1_E_SP(sp_idx),
			FIELD_PREP(PPE_L1_SP_DRR_ID, c->drr));

		ppe_w32(ppe, PPE_TM_L1_PORT_MAP(c->index),
			FIELD_PREP(PPE_L1_PORT_NUM, c->port));
	}
}

struct l0_cfg {
	u16 queue;
	u8 port;
	u8 sp;
	u8 cpri;
	u8 cdrr;
	u8 epri;
	u8 edrr;
};

static const struct l0_cfg l0_port0[] = {
	{   0, 0, 0, 0, 0, 0, 0 }, {   4, 0, 0, 0, 0, 0, 0 },
	{   8, 0, 0, 0, 0, 0, 0 }, { 256, 0, 0, 0, 0, 0, 0 },
	{ 260, 0, 0, 0, 0, 0, 0 },
	{   1, 0, 0, 1, 1, 1, 1 }, {   5, 0, 0, 1, 1, 1, 1 },
	{   9, 0, 0, 1, 1, 1, 1 }, { 257, 0, 0, 1, 1, 1, 1 },
	{ 261, 0, 0, 1, 1, 1, 1 },
	{   2, 0, 0, 2, 2, 2, 2 }, {   6, 0, 0, 2, 2, 2, 2 },
	{  10, 0, 0, 2, 2, 2, 2 }, { 258, 0, 0, 2, 2, 2, 2 },
	{ 262, 0, 0, 2, 2, 2, 2 },
	{   3, 0, 0, 3, 3, 3, 3 }, {   7, 0, 0, 3, 3, 3, 3 },
	{  11, 0, 0, 3, 3, 3, 3 }, { 259, 0, 0, 3, 3, 3, 3 },
	{ 263, 0, 0, 3, 3, 3, 3 },
};

static void ppe_l0_entry_write(struct qca_ppe *ppe, const struct l0_cfg *c)
{
	u32 sp_idx;

	ppe_w32(ppe, PPE_TM_L0_FLOW_MAP(c->queue),
		FIELD_PREP(PPE_L0_SP_ID, c->sp) |
		FIELD_PREP(PPE_L0_C_PRI, c->cpri) |
		FIELD_PREP(PPE_L0_E_PRI, c->epri) |
		FIELD_PREP(PPE_L0_C_DRR_WT, 1) |
		FIELD_PREP(PPE_L0_E_DRR_WT, 1));

	sp_idx = c->sp * 8 + c->cpri;
	ppe_w32(ppe, PPE_TM_L0_C_SP(sp_idx),
		FIELD_PREP(PPE_L0_SP_DRR_ID, c->cdrr));

	sp_idx = c->sp * 8 + c->epri;
	ppe_w32(ppe, PPE_TM_L0_E_SP(sp_idx),
		FIELD_PREP(PPE_L0_SP_DRR_ID, c->edrr));

	ppe_w32(ppe, PPE_TM_L0_PORT_MAP(c->queue),
		FIELD_PREP(PPE_L0_PORT_NUM, c->port));
}

struct port_l0_params {
	u16 ucast_base;
	u8 ucast_count;
	u16 mcast_base;
	u8 mcast_count;
	u8 sp_base;
	u8 cdrr_base;
	u8 port;
};

static const struct port_l0_params port_l0[] = {
	{ 144, 16, 272, 4, 36,  48, 1 },
	{ 160, 16, 276, 4, 40,  64, 2 },
	{ 176, 16, 280, 4, 44,  80, 3 },
	{ 192, 16, 284, 4, 48,  96, 4 },
	{ 208, 16, 288, 4, 52, 112, 5 },
	{ 224, 16, 292, 4, 56, 128, 6 },
	{ 240, 16, 296, 1, 60, 144, 7 },
};

static void ppe_l0_scheduler_init(struct qca_ppe *ppe)
{
	int i, j;

	for (i = 0; i < ARRAY_SIZE(l0_port0); i++)
		ppe_l0_entry_write(ppe, &l0_port0[i]);

	for (i = 0; i < ARRAY_SIZE(port_l0); i++) {
		const struct port_l0_params *p = &port_l0[i];
		u16 bases[] = { p->ucast_base, p->mcast_base };
		u8 counts[] = { p->ucast_count, p->mcast_count };
		int k;

		for (k = 0; k < 2; k++) {
			for (j = 0; j < counts[k]; j++) {
				struct l0_cfg c = {
					.queue = bases[k] + j,
					.port = p->port,
					.sp = p->sp_base + j / PPE_MAX_SP_PRI,
					.cpri = j % PPE_MAX_SP_PRI,
					.cdrr = p->cdrr_base + j,
					.epri = j % PPE_MAX_SP_PRI,
					.edrr = p->cdrr_base + j,
				};

				ppe_l0_entry_write(ppe, &c);
			}
		}
	}
}

static void ppe_edma_ring_map_init(struct qca_ppe *ppe)
{
	int i;

	ppe_w32(ppe, PPE_TM_RING_Q_MAP(0), 0xf);
	for (i = 1; i < 10; i++)
		ppe_w32(ppe, PPE_TM_RING_Q_MAP(0) + i * 4, 0);

	ppe_w32(ppe, PPE_TM_RING_Q_MAP(3), 0xf0);
	for (i = 1; i < 10; i++)
		ppe_w32(ppe, PPE_TM_RING_Q_MAP(3) + i * 4, 0);

	ppe_w32(ppe, PPE_TM_RING_Q_MAP(1), 0xf00);
	for (i = 1; i < 10; i++)
		ppe_w32(ppe, PPE_TM_RING_Q_MAP(1) + i * 4, 0);

	for (i = 0; i < 10; i++)
		ppe_w32(ppe, PPE_TM_RING_Q_MAP(2) + i * 4, 0);
	ppe_w32(ppe, PPE_TM_RING_Q_MAP(2) + 4 * 4, 0xffff);
}

static void ppe_qos_init(struct qca_ppe *ppe)
{
	int i;
	u32 qos_bits;

	qos_bits = FIELD_PREP(PPE_QOS_PREHEADER_PREC, 3) |
		   FIELD_PREP(PPE_QOS_DSCP_PREC, 1) |
		   FIELD_PREP(PPE_QOS_FLOW_PREC, 4) |
		   FIELD_PREP(PPE_QOS_ACL_PREC, 2);

	for (i = 0; i < PPE_NUM_PORTS; i++)
		ppe_m32(ppe, PPE_PRX_MRU_MTU_W1(i),
			PPE_QOS_PCP_GRP | PPE_QOS_DSCP_GRP |
			PPE_QOS_PREHEADER_PREC | PPE_QOS_PCP_PREC |
			PPE_QOS_DSCP_PREC | PPE_QOS_FLOW_PREC |
			PPE_QOS_ACL_PREC,
			qos_bits);
}

void ppe_scheduler_init(struct qca_ppe *ppe)
{
	ppe_tdm_init(ppe);
	ppe_bm_init(ppe);
	ppe_qm_init(ppe);
	ppe_l1_scheduler_init(ppe);
	ppe_l0_scheduler_init(ppe);
	ppe_edma_ring_map_init(ppe);
	ppe_qos_init(ppe);
}
