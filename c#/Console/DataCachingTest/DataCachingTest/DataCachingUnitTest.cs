namespace DataCachingTest
{
    using System;
    using System.Diagnostics;
    using System.Linq;
    using System.Text.RegularExpressions;

    using NUnit.Framework;

    [TestFixture]
    public class DataCachingUnitTest
    {
        [SetUp]
        protected void SetUp()
        {
            random_ = new Random();

            var cacheSizeFactor = random_.Next(1, 10);

            count_ = 10890; // random_.Next(100, 20000);

            dataSourceView_ = new DataSourceView(cacheSizeFactor)
            {
                DataSource = new DataSource()
            };
        }

        [Test]
        public void TestEverFailed()
        {
            var errorLog = @"
Expected data range: [56336, 67226), data cache range: [56336, 99896)
Expected data range: [68048, 78938), data cache range: [56336, 99896)
Expected data range: [77878, 88768), data cache range: [56336, 99896)
Expected data range: [50372, 61262), data cache range: [50372, 93932)
Expected data range: [78187, 89077), data cache range: [50372, 93932)
Expected data range: [8652, 19542), data cache range: [8652, 52212)
Expected data range: [30566, 41456), data cache range: [8652, 52212)
Expected data range: [147736, 158626), data cache range: [147736, 191296)
Expected data range: [115576, 126466), data cache range: [115576, 159136)
Expected data range: [31679, 42569), data cache range: [31679, 75239)
Expected data range: [59138, 70028), data cache range: [31679, 75239)
Expected data range: [217495, 228385), data cache range: [217495, 261055)
Expected data range: [180800, 191690), data cache range: [180800, 224360)
Expected data range: [125982, 136872), data cache range: [125982, 169542)
Expected data range: [97318, 108208), data cache range: [97318, 140878)
Expected data range: [198784, 209674), data cache range: [198784, 242344)
Expected data range: [48246, 59136), data cache range: [48246, 91806)
Expected data range: [233551, 244441), data cache range: [226440, 270000)
Expected data range: [145119, 156009), data cache range: [145119, 188679)
Expected data range: [63088, 73978), data cache range: [63088, 106648)
Expected data range: [140658, 151548), data cache range: [140658, 184218)
Expected data range: [151501, 162391), data cache range: [140658, 184218)
Expected data range: [48186, 59076), data cache range: [48186, 91746)
Expected data range: [48054, 58944), data cache range: [48054, 91614)
Expected data range: [120190, 131080), data cache range: [120190, 163750)
Expected data range: [219756, 230646), data cache range: [219756, 263316)
Expected data range: [103767, 114657), data cache range: [103767, 147327)
Expected data range: [191118, 202008), data cache range: [191118, 234678)
Expected data range: [208489, 219379), data cache range: [191118, 234678)
Expected data range: [67332, 78222), data cache range: [67332, 110892)
Expected data range: [116135, 127025), data cache range: [116135, 159695)
Expected data range: [227955, 238845), data cache range: [226440, 270000)
Expected data range: [19909, 30799), data cache range: [19909, 63469)
Expected data range: [177109, 187999), data cache range: [177109, 220669)
Expected data range: [94156, 105046), data cache range: [94156, 137716)
Expected data range: [136871, 147761), data cache range: [104201, 147761)
Expected data range: [31510, 42400), data cache range: [31510, 75070)
Expected data range: [13751, 24641), data cache range: [13751, 57311)
Expected data range: [249940, 260830), data cache range: [226440, 270000)
Expected data range: [148055, 158945), data cache range: [148055, 191615)
Expected data range: [250867, 261757), data cache range: [226440, 270000)
Expected data range: [42029, 52919), data cache range: [42029, 85589)
Expected data range: [171966, 182856), data cache range: [171966, 215526)
Expected data range: [200254, 211144), data cache range: [171966, 215526)
Expected data range: [145148, 156038), data cache range: [145148, 188708)
Expected data range: [87615, 98505), data cache range: [87615, 131175)
Expected data range: [219287, 230177), data cache range: [219287, 262847)
Expected data range: [229051, 239941), data cache range: [219287, 262847)
Expected data range: [173425, 184315), data cache range: [173425, 216985)
Expected data range: [193353, 204243), data cache range: [173425, 216985)
Expected data range: [166190, 177080), data cache range: [166190, 209750)
Expected data range: [228321, 239211), data cache range: [226440, 270000)
Expected data range: [254967, 265857), data cache range: [226440, 270000)
Expected data range: [228641, 239531), data cache range: [226440, 270000)
Expected data range: [239349, 250239), data cache range: [226440, 270000)
Expected data range: [174835, 185725), data cache range: [174835, 218395)
Expected data range: [19862, 30752), data cache range: [19862, 63422)
Expected data range: [29823, 40713), data cache range: [19862, 63422)
Expected data range: [200181, 211071), data cache range: [200181, 243741)
Expected data range: [128430, 139320), data cache range: [128430, 171990)
Expected data range: [174885, 185775), data cache range: [174885, 218445)
Expected data range: [109448, 120338), data cache range: [109448, 153008)
Expected data range: [209246, 220136), data cache range: [209246, 252806)
Expected data range: [48243, 59133), data cache range: [48243, 91803)
Expected data range: [185543, 196433), data cache range: [185543, 229103)
Expected data range: [101182, 112072), data cache range: [101182, 144742)
Expected data range: [197585, 208475), data cache range: [197585, 241145)
Expected data range: [3691, 14581), data cache range: [3691, 47251)
Expected data range: [31826, 42716), data cache range: [3691, 47251)
Expected data range: [230447, 241337), data cache range: [226440, 270000)
Expected data range: [167273, 178163), data cache range: [167273, 210833)
Expected data range: [34494, 45384), data cache range: [34494, 78054)
Expected data range: [253611, 264501), data cache range: [226440, 270000)
Expected data range: [267063, 270000), data cache range: [226440, 270000)
Expected data range: [82220, 93110), data cache range: [82220, 125780)
Expected data range: [98628, 109518), data cache range: [82220, 125780)
Expected data range: [249534, 260424), data cache range: [226440, 270000)
Expected data range: [117931, 128821), data cache range: [117931, 161491)
Expected data range: [172905, 183795), data cache range: [172905, 216465)
Expected data range: [32575, 43465), data cache range: [32575, 76135)
Expected data range: [468, 11358), data cache range: [468, 44028)
Expected data range: [144715, 155605), data cache range: [144715, 188275)
Expected data range: [17692, 28582), data cache range: [17692, 61252)
Expected data range: [15135, 26025), data cache range: [15135, 58695)
Expected data range: [171142, 182032), data cache range: [171142, 214702)
Expected data range: [157813, 168703), data cache range: [157813, 201373)
Expected data range: [242988, 253878), data cache range: [226440, 270000)
Expected data range: [61268, 72158), data cache range: [61268, 104828)
Expected data range: [207759, 218649), data cache range: [207759, 251319)
Expected data range: [189320, 200210), data cache range: [189320, 232880)
Expected data range: [117008, 127898), data cache range: [117008, 160568)
Expected data range: [1686, 12576), data cache range: [1686, 45246)
Expected data range: [83570, 94460), data cache range: [83570, 127130)
Expected data range: [121509, 132399), data cache range: [88839, 132399)
Expected data range: [243170, 254060), data cache range: [226440, 270000)
Expected data range: [141418, 152308), data cache range: [141418, 184978)
Expected data range: [102783, 113673), data cache range: [102783, 146343)
Expected data range: [123723, 134613), data cache range: [102783, 146343)
Expected data range: [14710, 25600), data cache range: [14710, 58270)
Expected data range: [43966, 54856), data cache range: [14710, 58270)
Expected data range: [160029, 170919), data cache range: [160029, 203589)
Expected data range: [215595, 226485), data cache range: [215595, 259155)
Expected data range: [197225, 208115), data cache range: [197225, 240785)
Expected data range: [212978, 223868), data cache range: [197225, 240785)
Expected data range: [26080, 36970), data cache range: [26080, 69640)
Expected data range: [131695, 142585), data cache range: [131695, 175255)
Expected data range: [244710, 255600), data cache range: [226440, 270000)
Expected data range: [257903, 268793), data cache range: [226440, 270000)
Expected data range: [146421, 157311), data cache range: [146421, 189981)
Expected data range: [140720, 151610), data cache range: [140720, 184280)
Expected data range: [195300, 206190), data cache range: [195300, 238860)
Expected data range: [171930, 182820), data cache range: [171930, 215490)
Expected data range: [126918, 137808), data cache range: [126918, 170478)
Expected data range: [167605, 178495), data cache range: [134935, 178495)
Expected data range: [127961, 138851), data cache range: [127961, 171521)
Expected data range: [30169, 41059), data cache range: [30169, 73729)
Expected data range: [91756, 102646), data cache range: [91756, 135316)
Expected data range: [194110, 205000), data cache range: [194110, 237670)
Expected data range: [147101, 157991), data cache range: [147101, 190661)
Expected data range: [27730, 38620), data cache range: [27730, 71290)
Expected data range: [128194, 139084), data cache range: [128194, 171754)
Expected data range: [136317, 147207), data cache range: [128194, 171754)
Expected data range: [65932, 76822), data cache range: [65932, 109492)
Expected data range: [112505, 123395), data cache range: [112505, 156065)
Expected data range: [113438, 124328), data cache range: [112505, 156065)
Expected data range: [165586, 176476), data cache range: [165586, 209146)
Expected data range: [220924, 231814), data cache range: [220924, 264484)
Expected data range: [132102, 142992), data cache range: [132102, 175662)
Expected data range: [23893, 34783), data cache range: [23893, 67453)
Expected data range: [210801, 221691), data cache range: [210801, 254361)
Expected data range: [265845, 270000), data cache range: [226440, 270000)
Expected data range: [125811, 136701), data cache range: [125811, 169371)
Expected data range: [103220, 114110), data cache range: [103220, 146780)
Expected data range: [128939, 139829), data cache range: [103220, 146780)
Expected data range: [142545, 153435), data cache range: [109875, 153435)
Expected data range: [54873, 65763), data cache range: [54873, 98433)
Expected data range: [217490, 228380), data cache range: [217490, 261050)
Expected data range: [74714, 85604), data cache range: [74714, 118274)
Expected data range: [259055, 269945), data cache range: [226440, 270000)
Expected data range: [39446, 50336), data cache range: [39446, 83006)
Expected data range: [183103, 193993), data cache range: [183103, 226663)
Expected data range: [255084, 265974), data cache range: [226440, 270000)
Expected data range: [184846, 195736), data cache range: [184846, 228406)
Expected data range: [67038, 77928), data cache range: [67038, 110598)
Expected data range: [264020, 270000), data cache range: [226440, 270000)
Expected data range: [215078, 225968), data cache range: [215078, 258638)
Expected data range: [144768, 155658), data cache range: [144768, 188328)
Expected data range: [185964, 196854), data cache range: [153294, 196854)
Expected data range: [263547, 270000), data cache range: [226440, 270000)
Expected data range: [213001, 223891), data cache range: [213001, 256561)
Expected data range: [49662, 60552), data cache range: [49662, 93222)
Expected data range: [178672, 189562), data cache range: [178672, 222232)
Expected data range: [246622, 257512), data cache range: [226440, 270000)
Expected data range: [256980, 267870), data cache range: [226440, 270000)
Expected data range: [185771, 196661), data cache range: [185771, 229331)
Expected data range: [23712, 34602), data cache range: [23712, 67272)
Expected data range: [149663, 160553), data cache range: [149663, 193223)
Expected data range: [84720, 95610), data cache range: [84720, 128280)
Expected data range: [99539, 110429), data cache range: [84720, 128280)
Expected data range: [130493, 141383), data cache range: [130493, 174053)
Expected data range: [180770, 191660), data cache range: [180770, 224330)
Expected data range: [112608, 123498), data cache range: [112608, 156168)
Expected data range: [234010, 244900), data cache range: [226440, 270000)
Expected data range: [205619, 216509), data cache range: [205619, 249179)
Expected data range: [144875, 155765), data cache range: [144875, 188435)
Expected data range: [69488, 80378), data cache range: [69488, 113048)
Expected data range: [68709, 79599), data cache range: [68709, 112269)
Expected data range: [267979, 270000), data cache range: [226440, 270000)
Expected data range: [25060, 35950), data cache range: [25060, 68620)
Expected data range: [73088, 83978), data cache range: [73088, 116648)
Expected data range: [82679, 93569), data cache range: [73088, 116648)
Expected data range: [17042, 27932), data cache range: [17042, 60602)
Expected data range: [205055, 215945), data cache range: [205055, 248615)
Expected data range: [107655, 118545), data cache range: [107655, 151215)
Expected data range: [114627, 125517), data cache range: [107655, 151215)
Expected data range: [143109, 153999), data cache range: [110439, 153999)
Expected data range: [221470, 232360), data cache range: [221470, 265030)
Expected data range: [268893, 270000), data cache range: [226440, 270000)
Expected data range: [118484, 129374), data cache range: [118484, 162044)
Expected data range: [168360, 179250), data cache range: [168360, 211920)
Expected data range: [20818, 31708), data cache range: [20818, 64378)
Expected data range: [34960, 45850), data cache range: [20818, 64378)
Expected data range: [138554, 149444), data cache range: [138554, 182114)
Expected data range: [80891, 91781), data cache range: [80891, 124451)
Expected data range: [161139, 172029), data cache range: [161139, 204699)
Expected data range: [87173, 98063), data cache range: [87173, 130733)
Expected data range: [149189, 160079), data cache range: [149189, 192749)
Expected data range: [116239, 127129), data cache range: [116239, 159799)
Expected data range: [213167, 224057), data cache range: [213167, 256727)
Expected data range: [118833, 129723), data cache range: [118833, 162393)
Expected data range: [175209, 186099), data cache range: [175209, 218769)
Expected data range: [132769, 143659), data cache range: [132769, 176329)
Expected data range: [245174, 256064), data cache range: [226440, 270000)
Expected data range: [128562, 139452), data cache range: [128562, 172122)
Expected data range: [128675, 139565), data cache range: [128562, 172122)
Expected data range: [70494, 81384), data cache range: [70494, 114054)
Expected data range: [21074, 31964), data cache range: [21074, 64634)
Expected data range: [249227, 260117), data cache range: [226440, 270000)
Expected data range: [192163, 203053), data cache range: [192163, 235723)
Expected data range: [194531, 205421), data cache range: [192163, 235723)
Expected data range: [146368, 157258), data cache range: [146368, 189928)
Expected data range: [146788, 157678), data cache range: [146368, 189928)
Expected data range: [160904, 171794), data cache range: [146368, 189928)
Expected data range: [190458, 201348), data cache range: [190458, 234018)
Expected data range: [130321, 141211), data cache range: [130321, 173881)
Expected data range: [32619, 43509), data cache range: [32619, 76179)
Expected data range: [243617, 254507), data cache range: [226440, 270000)
Expected data range: [138967, 149857), data cache range: [138967, 182527)
Expected data range: [142353, 153243), data cache range: [138967, 182527)
Expected data range: [42661, 53551), data cache range: [42661, 86221)
Expected data range: [72241, 83131), data cache range: [42661, 86221)
Expected data range: [150769, 161659), data cache range: [150769, 194329)
Expected data range: [236235, 247125), data cache range: [226440, 270000)
Expected data range: [201179, 212069), data cache range: [201179, 244739)
Expected data range: [109674, 120564), data cache range: [109674, 153234)
Expected data range: [145810, 156700), data cache range: [113140, 156700)
Expected data range: [244053, 254943), data cache range: [226440, 270000)
Expected data range: [153118, 164008), data cache range: [153118, 196678)
Expected data range: [44479, 55369), data cache range: [44479, 88039)
Expected data range: [57701, 68591), data cache range: [44479, 88039)
Expected data range: [190299, 201189), data cache range: [190299, 233859)
Expected data range: [222470, 233360), data cache range: [190299, 233859)
Expected data range: [54812, 65702), data cache range: [54812, 98372)
Expected data range: [176226, 187116), data cache range: [176226, 219786)
Expected data range: [167879, 178769), data cache range: [167879, 211439)
Expected data range: [219909, 230799), data cache range: [219909, 263469)
Expected data range: [41868, 52758), data cache range: [41868, 85428)
Expected data range: [76492, 87382), data cache range: [43822, 87382)
Expected data range: [248979, 259869), data cache range: [226440, 270000)
Expected data range: [44132, 55022), data cache range: [44132, 87692)
Expected data range: [122035, 132925), data cache range: [122035, 165595)
Expected data range: [242243, 253133), data cache range: [226440, 270000)
Expected data range: [76730, 87620), data cache range: [76730, 120290)
Expected data range: [193952, 204842), data cache range: [193952, 237512)
Expected data range: [21991, 32881), data cache range: [21991, 65551)
Expected data range: [144030, 154920), data cache range: [144030, 187590)
Expected data range: [144056, 154946), data cache range: [144030, 187590)
Expected data range: [218095, 228985), data cache range: [218095, 261655)
Expected data range: [220569, 231459), data cache range: [218095, 261655)
Expected data range: [128520, 139410), data cache range: [128520, 172080)
Expected data range: [113556, 124446), data cache range: [113556, 157116)
Expected data range: [10221, 21111), data cache range: [10221, 53781)
Expected data range: [243886, 254776), data cache range: [226440, 270000)
Expected data range: [170505, 181395), data cache range: [170505, 214065)
Expected data range: [46592, 57482), data cache range: [46592, 90152)
Expected data range: [24439, 35329), data cache range: [24439, 67999)
Expected data range: [166534, 177424), data cache range: [166534, 210094)
Expected data range: [43994, 54884), data cache range: [43994, 87554)
Expected data range: [18887, 29777), data cache range: [18887, 62447)
Expected data range: [252865, 263755), data cache range: [226440, 270000)
Expected data range: [96441, 107331), data cache range: [96441, 140001)
Expected data range: [137956, 148846), data cache range: [105286, 148846)
Expected data range: [204748, 215638), data cache range: [204748, 248308)
Expected data range: [134462, 145352), data cache range: [134462, 178022)
Expected data range: [4231, 15121), data cache range: [4231, 47791)
Expected data range: [193898, 204788), data cache range: [193898, 237458)
Expected data range: [91976, 102866), data cache range: [91976, 135536)
Expected data range: [254677, 265567), data cache range: [226440, 270000)
Expected data range: [22579, 33469), data cache range: [22579, 66139)
Expected data range: [180412, 191302), data cache range: [180412, 223972)
Expected data range: [260751, 270000), data cache range: [226440, 270000)
Expected data range: [167124, 178014), data cache range: [167124, 210684)
Expected data range: [159987, 170877), data cache range: [159987, 203547)
Expected data range: [98221, 109111), data cache range: [98221, 141781)
Expected data range: [190626, 201516), data cache range: [190626, 234186)
Expected data range: [99998, 110888), data cache range: [99998, 143558)
Expected data range: [74039, 84929), data cache range: [74039, 117599)
Expected data range: [42283, 53173), data cache range: [42283, 85843)
Expected data range: [179187, 190077), data cache range: [179187, 222747)
Expected data range: [235644, 246534), data cache range: [226440, 270000)
Expected data range: [1753, 12643), data cache range: [1753, 45313)
Expected data range: [25957, 36847), data cache range: [1753, 45313)
Expected data range: [202548, 213438), data cache range: [202548, 246108)
Expected data range: [185958, 196848), data cache range: [185958, 229518)
Expected data range: [214145, 225035), data cache range: [185958, 229518)
Expected data range: [180078, 190968), data cache range: [180078, 223638)
Expected data range: [248584, 259474), data cache range: [226440, 270000)
Expected data range: [154306, 165196), data cache range: [154306, 197866)
Expected data range: [129634, 140524), data cache range: [129634, 173194)
Expected data range: [143439, 154329), data cache range: [129634, 173194)
Expected data range: [53375, 64265), data cache range: [53375, 96935)
Expected data range: [267873, 270000), data cache range: [226440, 270000)
Expected data range: [57604, 68494), data cache range: [57604, 101164)
Expected data range: [266114, 270000), data cache range: [226440, 270000)
Expected data range: [217690, 228580), data cache range: [217690, 261250)
Expected data range: [254079, 264969), data cache range: [221409, 264969)
";

            var dataSourceView = new DataSourceView(4)
            {
                DataSource = new DataSource()
            };

            var lines = errorLog.Split(new string[] { "\r\n", "\n" }, StringSplitOptions.RemoveEmptyEntries);

            var positions = new int[lines.Length];
            var counts = new int[lines.Length];

            var regex = new Regex(@"\d+");

            for (int i = 0; i < lines.Length; ++i)
            {
                var matchesResult = regex.Matches(lines[i]);
                Debug.Assert(matchesResult.Count == 4);

                var start = Convert.ToInt32(matchesResult[0].ToString());
                var end = Convert.ToInt32(matchesResult[1].ToString());

                positions[i] = start;
                counts[i] = end - start;
            }

            for (var i = 0; i < positions.Length; ++i)
            {
                var data = dataSourceView.Read(positions[i], counts[i]).ToArray();

                for (var j = 0; j < dataSourceView.CachedData.Length; ++j)
                    Assert.AreEqual(dataSourceView.CachedDataStartPosition + j, dataSourceView.CachedData[j]);

                for (var j = 0; j < data.Length; ++j)
                    Assert.AreEqual(positions[i] + j, data[j]);
            }
        }

        [Test]
        public void TestMoveForward()
        {
            for (var i = 0; i < 100; ++i)
            {
                var data = dataSourceView_.Read(i * count_, count_).ToArray();

                for (var j = 0; j < dataSourceView_.CachedData.Length; ++j)
                    Assert.AreEqual(dataSourceView_.CachedDataStartPosition + j, dataSourceView_.CachedData[j]);

                for (var j = 0; j < data.Length; ++j)
                    Assert.AreEqual(i * count_ + j, data[j]);
            }
        }

        [Test]
        public void TestRandomly()
        {
            var positions = Enumerable.Range(100, 1000).Select(i => random_.Next(0, dataSourceView_.DataSource.Length)).ToArray();
            for (var i = 0; i < positions.Length; ++i)
            {
                var data = dataSourceView_.Read(positions[i], count_).ToArray();

                for (var j = 0; j < dataSourceView_.CachedData.Length; ++j)
                    Assert.AreEqual(dataSourceView_.CachedDataStartPosition + j, dataSourceView_.CachedData[j]);

                for (var j = 0; j < data.Length; ++j)
                    Assert.AreEqual(positions[i] + j, data[j]);
            }
        }

        private Random random_;
        private int count_;
        private DataSourceView dataSourceView_;
    }
}
