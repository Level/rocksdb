﻿/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#pragma once
#include <aws/s3/S3_EXPORTS.h>
#include <aws/s3/model/BucketLocationConstraint.h>
#include <aws/s3/model/LocationInfo.h>
#include <aws/s3/model/BucketInfo.h>
#include <utility>

namespace Aws
{
namespace Utils
{
namespace Xml
{
  class XmlNode;
} // namespace Xml
} // namespace Utils
namespace S3
{
namespace Model
{

  /**
   * <p>The configuration information for the bucket.</p><p><h3>See Also:</h3>   <a
   * href="http://docs.aws.amazon.com/goto/WebAPI/s3-2006-03-01/CreateBucketConfiguration">AWS
   * API Reference</a></p>
   */
  class CreateBucketConfiguration
  {
  public:
    AWS_S3_API CreateBucketConfiguration();
    AWS_S3_API CreateBucketConfiguration(const Aws::Utils::Xml::XmlNode& xmlNode);
    AWS_S3_API CreateBucketConfiguration& operator=(const Aws::Utils::Xml::XmlNode& xmlNode);

    AWS_S3_API void AddToNode(Aws::Utils::Xml::XmlNode& parentNode) const;


    /**
     * <p>Specifies the Region where the bucket will be created. You might choose a
     * Region to optimize latency, minimize costs, or address regulatory requirements.
     * For example, if you reside in Europe, you will probably find it advantageous to
     * create buckets in the Europe (Ireland) Region. For more information, see <a
     * href="https://docs.aws.amazon.com/AmazonS3/latest/dev/UsingBucket.html#access-bucket-intro">Accessing
     * a bucket</a> in the <i>Amazon S3 User Guide</i>.</p> <p>If you don't specify a
     * Region, the bucket is created in the US East (N. Virginia) Region (us-east-1) by
     * default.</p>  <p>This functionality is not supported for directory
     * buckets.</p> 
     */
    inline const BucketLocationConstraint& GetLocationConstraint() const{ return m_locationConstraint; }

    /**
     * <p>Specifies the Region where the bucket will be created. You might choose a
     * Region to optimize latency, minimize costs, or address regulatory requirements.
     * For example, if you reside in Europe, you will probably find it advantageous to
     * create buckets in the Europe (Ireland) Region. For more information, see <a
     * href="https://docs.aws.amazon.com/AmazonS3/latest/dev/UsingBucket.html#access-bucket-intro">Accessing
     * a bucket</a> in the <i>Amazon S3 User Guide</i>.</p> <p>If you don't specify a
     * Region, the bucket is created in the US East (N. Virginia) Region (us-east-1) by
     * default.</p>  <p>This functionality is not supported for directory
     * buckets.</p> 
     */
    inline bool LocationConstraintHasBeenSet() const { return m_locationConstraintHasBeenSet; }

    /**
     * <p>Specifies the Region where the bucket will be created. You might choose a
     * Region to optimize latency, minimize costs, or address regulatory requirements.
     * For example, if you reside in Europe, you will probably find it advantageous to
     * create buckets in the Europe (Ireland) Region. For more information, see <a
     * href="https://docs.aws.amazon.com/AmazonS3/latest/dev/UsingBucket.html#access-bucket-intro">Accessing
     * a bucket</a> in the <i>Amazon S3 User Guide</i>.</p> <p>If you don't specify a
     * Region, the bucket is created in the US East (N. Virginia) Region (us-east-1) by
     * default.</p>  <p>This functionality is not supported for directory
     * buckets.</p> 
     */
    inline void SetLocationConstraint(const BucketLocationConstraint& value) { m_locationConstraintHasBeenSet = true; m_locationConstraint = value; }

    /**
     * <p>Specifies the Region where the bucket will be created. You might choose a
     * Region to optimize latency, minimize costs, or address regulatory requirements.
     * For example, if you reside in Europe, you will probably find it advantageous to
     * create buckets in the Europe (Ireland) Region. For more information, see <a
     * href="https://docs.aws.amazon.com/AmazonS3/latest/dev/UsingBucket.html#access-bucket-intro">Accessing
     * a bucket</a> in the <i>Amazon S3 User Guide</i>.</p> <p>If you don't specify a
     * Region, the bucket is created in the US East (N. Virginia) Region (us-east-1) by
     * default.</p>  <p>This functionality is not supported for directory
     * buckets.</p> 
     */
    inline void SetLocationConstraint(BucketLocationConstraint&& value) { m_locationConstraintHasBeenSet = true; m_locationConstraint = std::move(value); }

    /**
     * <p>Specifies the Region where the bucket will be created. You might choose a
     * Region to optimize latency, minimize costs, or address regulatory requirements.
     * For example, if you reside in Europe, you will probably find it advantageous to
     * create buckets in the Europe (Ireland) Region. For more information, see <a
     * href="https://docs.aws.amazon.com/AmazonS3/latest/dev/UsingBucket.html#access-bucket-intro">Accessing
     * a bucket</a> in the <i>Amazon S3 User Guide</i>.</p> <p>If you don't specify a
     * Region, the bucket is created in the US East (N. Virginia) Region (us-east-1) by
     * default.</p>  <p>This functionality is not supported for directory
     * buckets.</p> 
     */
    inline CreateBucketConfiguration& WithLocationConstraint(const BucketLocationConstraint& value) { SetLocationConstraint(value); return *this;}

    /**
     * <p>Specifies the Region where the bucket will be created. You might choose a
     * Region to optimize latency, minimize costs, or address regulatory requirements.
     * For example, if you reside in Europe, you will probably find it advantageous to
     * create buckets in the Europe (Ireland) Region. For more information, see <a
     * href="https://docs.aws.amazon.com/AmazonS3/latest/dev/UsingBucket.html#access-bucket-intro">Accessing
     * a bucket</a> in the <i>Amazon S3 User Guide</i>.</p> <p>If you don't specify a
     * Region, the bucket is created in the US East (N. Virginia) Region (us-east-1) by
     * default.</p>  <p>This functionality is not supported for directory
     * buckets.</p> 
     */
    inline CreateBucketConfiguration& WithLocationConstraint(BucketLocationConstraint&& value) { SetLocationConstraint(std::move(value)); return *this;}


    /**
     * <p>Specifies the location where the bucket will be created.</p> <p>For directory
     * buckets, the location type is Availability Zone.</p>  <p>This
     * functionality is only supported by directory buckets.</p> 
     */
    inline const LocationInfo& GetLocation() const{ return m_location; }

    /**
     * <p>Specifies the location where the bucket will be created.</p> <p>For directory
     * buckets, the location type is Availability Zone.</p>  <p>This
     * functionality is only supported by directory buckets.</p> 
     */
    inline bool LocationHasBeenSet() const { return m_locationHasBeenSet; }

    /**
     * <p>Specifies the location where the bucket will be created.</p> <p>For directory
     * buckets, the location type is Availability Zone.</p>  <p>This
     * functionality is only supported by directory buckets.</p> 
     */
    inline void SetLocation(const LocationInfo& value) { m_locationHasBeenSet = true; m_location = value; }

    /**
     * <p>Specifies the location where the bucket will be created.</p> <p>For directory
     * buckets, the location type is Availability Zone.</p>  <p>This
     * functionality is only supported by directory buckets.</p> 
     */
    inline void SetLocation(LocationInfo&& value) { m_locationHasBeenSet = true; m_location = std::move(value); }

    /**
     * <p>Specifies the location where the bucket will be created.</p> <p>For directory
     * buckets, the location type is Availability Zone.</p>  <p>This
     * functionality is only supported by directory buckets.</p> 
     */
    inline CreateBucketConfiguration& WithLocation(const LocationInfo& value) { SetLocation(value); return *this;}

    /**
     * <p>Specifies the location where the bucket will be created.</p> <p>For directory
     * buckets, the location type is Availability Zone.</p>  <p>This
     * functionality is only supported by directory buckets.</p> 
     */
    inline CreateBucketConfiguration& WithLocation(LocationInfo&& value) { SetLocation(std::move(value)); return *this;}


    /**
     * <p>Specifies the information about the bucket that will be created.</p> 
     * <p>This functionality is only supported by directory buckets.</p> 
     */
    inline const BucketInfo& GetBucket() const{ return m_bucket; }

    /**
     * <p>Specifies the information about the bucket that will be created.</p> 
     * <p>This functionality is only supported by directory buckets.</p> 
     */
    inline bool BucketHasBeenSet() const { return m_bucketHasBeenSet; }

    /**
     * <p>Specifies the information about the bucket that will be created.</p> 
     * <p>This functionality is only supported by directory buckets.</p> 
     */
    inline void SetBucket(const BucketInfo& value) { m_bucketHasBeenSet = true; m_bucket = value; }

    /**
     * <p>Specifies the information about the bucket that will be created.</p> 
     * <p>This functionality is only supported by directory buckets.</p> 
     */
    inline void SetBucket(BucketInfo&& value) { m_bucketHasBeenSet = true; m_bucket = std::move(value); }

    /**
     * <p>Specifies the information about the bucket that will be created.</p> 
     * <p>This functionality is only supported by directory buckets.</p> 
     */
    inline CreateBucketConfiguration& WithBucket(const BucketInfo& value) { SetBucket(value); return *this;}

    /**
     * <p>Specifies the information about the bucket that will be created.</p> 
     * <p>This functionality is only supported by directory buckets.</p> 
     */
    inline CreateBucketConfiguration& WithBucket(BucketInfo&& value) { SetBucket(std::move(value)); return *this;}

  private:

    BucketLocationConstraint m_locationConstraint;
    bool m_locationConstraintHasBeenSet = false;

    LocationInfo m_location;
    bool m_locationHasBeenSet = false;

    BucketInfo m_bucket;
    bool m_bucketHasBeenSet = false;
  };

} // namespace Model
} // namespace S3
} // namespace Aws
